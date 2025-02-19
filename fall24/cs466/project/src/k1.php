
<html>  
  <head>
    <title>K1</title>
    <link rel="stylesheet" href="style.css">
  </head>
  <body>
<?php




ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);
session_start();
require_once 'setup_karaoke.php';

try {
    $dsn = "mysql:host=$hostname;dbname=$dbname";
    $pdo = new PDO($dsn, $username, $password);
}
catch (PDOException $e) {
    echo "Connection to database failed: " . $e->getMessage();
}
?>
<?php

if ((isset($_POST['keep_searching']) && $_POST['keep_searching'] == 'No') || empty($_POST)) {
        session_destroy();
}

if (!isset($_SESSION['sort_count'])) {
    $_SESSION['sort_count'] = 0;
}
function is_sorted() {
    return isset($_POST['sort_method']);

}


echo "
   <div class=heading>
     <form> 
       <button class=chpage type='button' onclick=location.href='dj_page.php'>DJ Interface</button>
     </form>
    <div class=_welcome><h1>Welcome to Karaoke!</h1></div>
    <div class=_exit_button>
        <form action='k1.php' method='POST'>
            <button type='submit' name='action' value='exit'>Exit Session</button>
        </form>
    </div>
   </div>";

if (is_sorted() || isset($_POST['keep_searching']) && $_POST['keep_searching'] == 'Yes') {

    // helps keep the page intact when sorting.
    if (isset($_POST['keep_searching'])) { $_SESSION['last_message'] = "" ;}
    echo "<div class=_yihbsr><p>$_SESSION[last_message]</p></div>";

    // display search bar.
    echo "
                <div class=search_bar>
                <form action='k1.php' method='POST'>
                    <label for='search_query'>Search for a Song:</label>
                    <input type='text' id='search_query' name='search_query' placeholder='Enter your search...' required>
                    <label for='search_criteria'>Search By:</label>
                    <select id='search_criteria' name='search_criteria'>
                        <option value='TITLE'>Title</option>
                        <option value='ARTISTNAME'>Artist</option>
                        <option value='CNAME'>Contributor</option>
                    </select> <button id='hide_ugly_button' type='submit' name='action' value='search_song'>Search</button>
                </form></div>";
    

    if (is_sorted()) {
        // display new song table with sort.
        $sort_method = strtoupper($_POST['sort_method']);
        if (($sort_method) == 'CONTRIBUTOR') $sort_method = 'cname';
        else if ($sort_method == 'VERSION') $sort_method = 'files';

        if ($_SESSION['sort_count'] % 2 != 0) {
            $order_by = 'ASC';
        }
        else {
            $order_by = 'DESC';
        }

        $songs = $pdo->query("SELECT SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME,
            GROUP_CONCAT(DISTINCT CONTRIBUTOR.CNAME SEPARATOR ', ') AS `CONTRIBUTORS`,
            GROUP_CONCAT(DISTINCT KARAOKEFILE.VERSION SEPARATOR ', ') AS FILES
            FROM SONG
            LEFT JOIN CONTRIBUTE ON SONG.SONGID = CONTRIBUTE.SONGID
            LEFT JOIN CONTRIBUTOR ON CONTRIBUTE.CONTRIBUTORID = CONTRIBUTOR.CONTRIBUTORID
            LEFT JOIN KARAOKEFILE ON SONG.SONGID = KARAOKEFILE.SONGID 
            GROUP BY SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME order by $sort_method $order_by;");

        $_SESSION['sort_count']++;

    }
    else {
        $songs = $pdo->query("SELECT SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME,
            GROUP_CONCAT(DISTINCT CONTRIBUTOR.CNAME SEPARATOR ', ') AS `CONTRIBUTORS`,
            GROUP_CONCAT(DISTINCT KARAOKEFILE.VERSION SEPARATOR ', ') AS FILES
            FROM SONG
            LEFT JOIN CONTRIBUTE ON SONG.SONGID = CONTRIBUTE.SONGID
            LEFT JOIN CONTRIBUTOR ON CONTRIBUTE.CONTRIBUTORID = CONTRIBUTOR.CONTRIBUTORID
            LEFT JOIN KARAOKEFILE ON SONG.SONGID = KARAOKEFILE.SONGID 
            GROUP BY SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME");

    }

    draw_big_table($songs);

}

function too_large() {
        if ($_POST['pay_amount'] > 999) {
         echo "<p class=_yihbsr> Please consider paying a smaller amount (limit is $1000)</p>
                <div class=pay_amount><form action=k1.php method=POST>
                
                <label for=pay_amount>Enter Amount</label>
                <input id=pay_amount type=number name=pay_amount min=1 required>
                </form></div>
            ";
        return true;
     }
    return false;
}

 if (isset($_POST['pay_amount']) || (isset($_POST['action']) && $_POST['action'] == 'free_queue')) {
    $queue_type = isset($_POST['pay_amount']) ? 'P' : 'F';
    $dont_run = false;
    $_POST['action'] ?? $dont_run = too_large();

    if (!$dont_run) {
    // Insert the user's pick into the PICK table
    $insert_pick = $pdo->prepare("INSERT INTO PICK (QUEUETYPE, USERID, SONGID, FILEID, PAID, TIME) VALUES (:queue_type, :user_id, :song_id, :file_id, :paid, :time)");
    $insert_pick->execute([
        'queue_type' => $queue_type,
        'user_id' => $_SESSION['user_id'],
        'song_id' => $_SESSION['selected_song_id'][count($_SESSION['selected_song_id']) - 1],
        'file_id' => $_SESSION['selected_karaoke_file'],
        'paid' => ($queue_type === 'P') ? $_POST['pay_amount'] : 0.00,
        'time' => date('Y-m-d H:i:s')
    ]);
    echo "<div class=_yihbsr><p>Your selection has been recorded in the queue as " . ($queue_type === 'P' ? 'Premium' : 'Free') . ".</p>
        <p> Would you like to select another song?</p> 
        <form action=k1.php method=POST> 
        <input class=keep_searching type=submit value=Yes name=keep_searching>
        <button class=keep_searching type=submit value=exit_nodelete name=action>No</button>
        </form></div>";

    }
}

else {

    // Handle actions based on user input
   if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['action'])) {
        if ($_POST['action'] == 'yes_to_start') {

            // Prompt the user for their information
            echo " <div class=_name_prompt>
            <form action='k1.php' method='POST'>
                <label for='fname'>First Name:</label>
                <input type='text' id='fname' name='fname' required>
                <label for='lname'>Last Name:</label>
                <input type='text' id='lname' name='lname' required>
                <button type='submit' name='action' value='submit_user'>Submit</button>
            </form></div>";

        } elseif ($_POST['action'] == 'submit_user') {

            // Insert the user's information into the USER table
            if (!empty($_POST['fname']) && !empty($_POST['lname'])) {
                $insert_user = $pdo->prepare("INSERT INTO USER (FNAME, LNAME) VALUES (:fname, :lname)");
                $insert_user->execute([
                    'fname' => htmlspecialchars($_POST['fname']),
                    'lname' => htmlspecialchars($_POST['lname'])
                ]);
                $_SESSION['user_id'] = $pdo->lastInsertId();
                $_SESSION['fname'] = $_POST['fname'];
                $_SESSION['lname'] = $_POST['lname'];

                $_SESSION['last_message'] = 'Your information has been successfully recorded.';
                echo "<div class=_yihbsr><p>$_SESSION[last_message]</p></div>";

                

                // Display the list of available songs
                $songs = $pdo->query("SELECT SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME,
                                             GROUP_CONCAT(DISTINCT CONTRIBUTOR.CNAME SEPARATOR ', ') AS CONTRIBUTORS,
                                             GROUP_CONCAT(DISTINCT KARAOKEFILE.VERSION SEPARATOR ', ') AS FILES
                                      FROM SONG
                                      LEFT JOIN CONTRIBUTE ON SONG.SONGID = CONTRIBUTE.SONGID
                                      LEFT JOIN CONTRIBUTOR ON CONTRIBUTE.CONTRIBUTORID = CONTRIBUTOR.CONTRIBUTORID
                                      LEFT JOIN KARAOKEFILE ON SONG.SONGID = KARAOKEFILE.SONGID
                                      GROUP BY SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME");


                // Display search form
                echo "
                <div class=search_bar>
                <form action='k1.php' method='POST'>
                    <label for='search_query'>Search for a Song:</label>
                    <input type='text' id='search_query' name='search_query' placeholder='Enter your search...' required>
                    <label for='search_criteria'>Search By:</label>
                    <select id='search_criteria' name='search_criteria'>
                        <option value='TITLE'>Title</option>
                        <option value='ARTISTNAME'>Artist</option>
                        <option value='CNAME'>Contributor</option>
                    </select>
                    <button id='hide_ugly_button' type='submit' name='action' value='search_song'>Search</button>
                </form></div>";


                draw_big_table($songs);

            } else {
                echo '<p>Please provide both your first and last name.</p>';
            }

        } elseif ($_POST['action'] == 'search_song') {
            // Handle song search
            if (!empty($_POST['search_query']) && !empty($_POST['search_criteria'])) {
                $searchQuery = htmlspecialchars($_POST['search_query']);
                $searchCriteria = $_POST['search_criteria'];

                $stmt = $pdo->prepare("SELECT SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME,
                                              GROUP_CONCAT(DISTINCT CONTRIBUTOR.CNAME SEPARATOR ', ') AS CONTRIBUTORS,
                                              GROUP_CONCAT(DISTINCT KARAOKEFILE.VERSION SEPARATOR ', ') AS FILES,
                                              KARAOKEFILE.FILEID
                                       FROM SONG
                                       LEFT JOIN CONTRIBUTE ON SONG.SONGID = CONTRIBUTE.SONGID
                                       LEFT JOIN CONTRIBUTOR ON CONTRIBUTE.CONTRIBUTORID = CONTRIBUTOR.CONTRIBUTORID
                                       LEFT JOIN KARAOKEFILE ON SONG.SONGID = KARAOKEFILE.SONGID
                                       WHERE {$searchCriteria} LIKE :query
                                       GROUP BY SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME, KARAOKEFILE.FILEID");
                $stmt->execute(['query' => "%$searchQuery%"]);
                $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

                if ($results) {
                    displaySearchResults($results);
                } else {
                    $_SESSION['last_message'] = 'No results found for your search query. Please try again.';

                    echo "<div class=_yihbsr><p>$_SESSION[last_message]</p></div>";
                    // Redisplay the search form
                    echo "<div class=search_bar>
                    <form action='k1.php' method='POST'>
                        <label for='search_query'>Search for a Song:</label>
                        <input type='text' id='search_query' name='search_query' placeholder='Enter your search...' required>
                        <label for='search_criteria'>Search By:</label>
                        <select id='search_criteria' name='search_criteria'>
                            <option value='TITLE'>Title</option>
                            <option value='ARTISTNAME'>Artist</option>
                            <option value='CNAME'>Contributor</option>
                        </select>
                        <button id=hide_ugly_button type='submit' name='action' value='search_song'>Search</button>
                    </form></div>";
            $songs = $pdo->query("SELECT SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME,
            GROUP_CONCAT(DISTINCT CONTRIBUTOR.CNAME SEPARATOR ', ') AS `CONTRIBUTORS`,
            GROUP_CONCAT(DISTINCT KARAOKEFILE.VERSION SEPARATOR ', ') AS FILES
            FROM SONG
            LEFT JOIN CONTRIBUTE ON SONG.SONGID = CONTRIBUTE.SONGID
            LEFT JOIN CONTRIBUTOR ON CONTRIBUTE.CONTRIBUTORID = CONTRIBUTOR.CONTRIBUTORID
            LEFT JOIN KARAOKEFILE ON SONG.SONGID = KARAOKEFILE.SONGID 
            GROUP BY SONG.SONGID, SONG.TITLE, SONG.ARTISTNAME");
            draw_big_table($songs);


                }
            } else {
                echo "<p>Please enter a search query and select a search criteria.</p>";
            }
        } elseif ($_POST['action'] == 'select_song') {

            // Prompt the user to decide on premium or free queue
            if (isset($_POST['song_id']) && isset($_POST['karaoke_file'])) {

                if (isset($_SESSION['selected_song_id']) && in_array($_POST['song_id'], $_SESSION['selected_song_id'])) {

                    echo "<div class=_yihbsr><p>You have already choosen that song. Please select differently.</p>

                        <p> Would you like to select another song?</p> 
                        <form action=k1.php method=POST> 
                        <input class=keep_searching type=submit value=Yes name=keep_searching>
                        <button class=keep_searching type=submit value=exit_nodelete name=action>No</button>
                        </form></div>";
                }
                else {

                    if (!isset($_SESSION['selected_song_id'])) {
                        $_SESSION['selected_song_id'] = array();
                    }

                    array_push($_SESSION['selected_song_id'], $_POST['song_id']);

                    $_SESSION['selected_karaoke_file'] = htmlspecialchars($_POST['karaoke_file']);
                    $last_song_index = count($_SESSION['selected_song_id']) - 1;
                    $last_song = $_SESSION['selected_song_id'][$last_song_index];
                    echo "
                <div class=_yhss_><p>You have selected the song with ID $last_song and karaoke file version: {$_SESSION['selected_karaoke_file']}.</p> <p>Would you like to pay for the premium queue?</p></div>
                <div class=_yhssf_><form action='k1.php' method='POST'>
                    <button type='submit' name='action' value='premium_queue'>Yes, Pay</button>
                    <button type='submit' name='action' value='free_queue'>No, Free Queue</button>
                </form></div>";
                }

            }

        } elseif ($_POST['action'] == 'premium_queue') {
            $_SESSION['queue_type'] = $_POST['action'];
            
            echo "
                <div class=pay_amount><form action=k1.php method=POST>
                <label for=pay_amount>Enter Amount</label>
                <input id=pay_amount type=number name=pay_amount min=1 required>
                </form></div>
            ";
        } 

        elseif ($_POST['action'] == 'exit') {
            
            // Handle session exit
            if (isset($_SESSION['user_id'])) {
                // Delete entries from PICK table
                $deletePickStmt = $pdo->prepare("DELETE FROM PICK WHERE USERID = :user_id");
                $deletePickStmt->execute(['user_id' => $_SESSION['user_id']]);

                // Delete the user from USER table
                $deleteUserStmt = $pdo->prepare("DELETE FROM USER WHERE USERID = :user_id");
                $deleteUserStmt->execute(['user_id' => $_SESSION['user_id']]);

                unset($_SESSION['user_id']);
            }

            echo "<div class=_yihbsr><p>Your session has been ended. Goodbye! The next user can now start.</p></div>";
            echo "
            <div class=_start>
            <form action='k1.php' method='POST'>
                <button type='submit' name='action' value='yes_to_start'>Start New Session</button>
            </form></div>";
        }

        elseif ($_POST['action'] == 'exit_nodelete') {
            session_destroy();
            echo "<div class=_yihbsr><p>Your session has been ended. Goodbye! The next user can now start.</p></div>";
            echo "
            <div class=_start>
            <form action='k1.php' method='POST'>
                <button type='submit' name='action' value='yes_to_start'>Start New Session</button>
            </form></div>";
        }
    } 
   
     
    else {
        if (!isset($_POST['keep_searching']) && !is_sorted()) {
            // Initial welcome screen
            echo " <div class=_start>
                <form action='k1.php' method='POST'>
                <button type='submit' name='action' value='yes_to_start'>Start</button>
                </form></div>";
        }
    }
}


// Function to display search results
function displaySearchResults($results)
{
    if ($results) {
        echo "<div class=_yihbsr><h3>Search Results</h3></div>";

        echo "<div class=_song_table><table><thead>
                <tr><th>Song ID</th><th>Title</th><th>Artist Name</th><th>Contributors</th><th>Files</th><th>Select</th></tr></thead><tbody>";

        foreach ($results as $row) {
            echo "<tr>
                    <td>{$row['SONGID']}</td>
                    <td>{$row['TITLE']}</td>
                    <td>{$row['ARTISTNAME']}</td>
                    <td>{$row['CONTRIBUTORS']}</td>
                    <td>{$row['FILES']}</td>
                    <td>
                        <form action='k1.php' method='POST'>
                            <input type='hidden' name='song_id' value='{$row['SONGID']}'>
                            <input type='hidden' name='karaoke_file' value='{$row['FILEID']}'>
                            <button type='submit' name='action' value='select_song'>Select</button>
                        </form>
                    </td>
                  </tr>";
        }
        echo "</tbody></table></div>";
    } else {
        echo "<p>No results found.</p>";
    }
}
function draw_big_table($songs) {


    echo "<div class=_a_songs><h3>Available Songs</h3></div>
        <div class=_song_table><form action=k1.php method=POST><table><thead>

        <tr>
        <th><input class=btn type=submit value=\"SongID\" name=sort_method></th>
        <th><input class=btn type=submit value=\"Title\" name=sort_method></th>
        <th><input class=btn type=submit value=\"Artistname\" name=sort_method></th>
        <th><input class=btn type=submit value=\"Contributor\" name=sort_method></th>
        <th><input class=btn type=submit value=\"Version\" name=sort_method></th>
        </tr>
        </thead>
        <tbody>";

        foreach ($songs->fetchAll(PDO::FETCH_ASSOC) as $song) {
            echo "<tr>
                <td>{$song['SONGID']}</td>
                <td>{$song['TITLE']}</td>
                <td>{$song['ARTISTNAME']}</td>
                <td>{$song['CONTRIBUTORS']}</td>
                <td>{$song['FILES']}</td>
                </tr>";
        }
        echo "</tbody></table></div>";
}
?>
  </body>
</html>

