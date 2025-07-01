<!DOCTYPE html>
<html>
<head>
    <title>DJ Interface</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<header class="heading2">
    <form>
        <button class="chpage" type="button" onclick="location.href='k1.php'">User Interface</button>
    </form>
</header>
<main>
<?php
ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);
require_once('setup_karaoke.php');
session_start();

// Fixed the paid queue not sorting correctly.
// split the prio queue sort counter into two seperate counters
// sort by asc first instead of desc for paid.
// Fixed the weird bug with the background blur.
//
// fixed bug with keep searching logic. $SESSION_['selected_song_id'] is now an array 
// and can now save all the songs the user selects, rather than the most recent one.

try { 

    $dsn = "mysql:host=$hostname;dbname=$dbname";
    $pdo = new PDO($dsn, $username, $password);
}

catch (PDOException $e) {
    echo "Connection to database failed: " . $e->getMessage();
}


// Initilizing our three sort counters.
if (!isset($_SESSION['sort_counter_free'])) {
    $_SESSION['sort_counter_free'] = 0;
}
if (!isset($_SESSION['sort_counter_prio_time'])) {
    $_SESSION['sort_counter_prio_time'] = 0;
}
if (!isset($_SESSION['sort_counter_prio_paid'])) {
    $_SESSION['sort_counter_prio_paid'] = 0;
}

    // Checks for the user hitting any of the sort buttons.
    if (isset($_POST['sort_free']) || isset($_POST['sort_prio_paid']) || isset($_POST['sort_prio_time'])) {

        // Gets the right sorting key from POST.
        $key_name = isset($_POST['sort_free']) ? 'sort_free' : (isset($_POST['sort_prio_paid']) ? 'sort_prio_paid' : 'sort_prio_time');

        // Increments the right sort counter.
        $key_name == 'sort_prio_paid' ? ($_SESSION['sort_counter_prio_paid']++) :($key_name == 'sort_prio_time' ? $_SESSION['sort_counter_prio_time']++ : $_SESSION['sort_counter_free']++);

        // Get the right column to order by.
        $sort_column = $_POST[$key_name] == 'Amount Paid' ? 'PAID' : 'TIME';


        // Maps the sort type to its counter.
        $array = array('sort_free' => 'sort_counter_free', 'sort_prio_paid' => 'sort_counter_prio_paid', 'sort_prio_time' => 'sort_counter_prio_time');


        // TIME column will naturally always be defaulted to ascending order.
        // So im splitting this into two parts so the time sorts by desc first.
        if ($key_name != 'sort_free' && $key_name != 'sort_prio_time') { 
            ($_SESSION[$array[$key_name]] % 2 != 0) ? $sort_by = 'ASC' :$sort_by = 'DESC';
        }
        else {
            ($_SESSION[$array[$key_name]] % 2 == 0) ? $sort_by = 'ASC' :$sort_by = 'DESC';
        }
        
    }


    echo "<div class=dj_iff><h1>DJ Interface</h1></div>";

    // Handle DJ actions (remove user from queue).
    if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['user_id'], $_POST['song_id'])) {
        // Remove user from the queue using USERID and SONGID
        $userId = htmlspecialchars($_POST['user_id']);
        $songId = htmlspecialchars($_POST['song_id']);
        $deleteStmt = $pdo->prepare("DELETE FROM PICK WHERE USERID = :user_id AND SONGID = :song_id");
        $deleteStmt->execute(['user_id' => $userId, 'song_id' => $songId]);
        echo "<div class=dj_if><p>User has been removed from the queue.</p></div>";
    }


    // query + draw the premium queue
    echo "<div class=dj_if><h2>Premium Queue</h2></div>";
    if (isset($_POST['sort_prio_time']) || isset($_POST['sort_prio_paid'])) {

        $premiumQueue = $pdo->query("
        SELECT PICK.USERID, PICK.SONGID, USER.FNAME, USER.LNAME, SONG.TITLE, SONG.ARTISTNAME, KARAOKEFILE.VERSION, PAID, TIME
        FROM PICK
        JOIN USER ON PICK.USERID = USER.USERID
        JOIN SONG ON PICK.SONGID = SONG.SONGID
        JOIN KARAOKEFILE ON PICK.FILEID = KARAOKEFILE.FILEID
        WHERE PICK.QUEUETYPE = 'P'
        ORDER BY $sort_column $sort_by;

    ");
        $_SESSION['sort_counter_free'] = 0;
    }
    else {
        $premiumQueue = $pdo->query("
        SELECT PICK.USERID, PICK.SONGID, USER.FNAME, USER.LNAME, SONG.TITLE, SONG.ARTISTNAME, KARAOKEFILE.VERSION, PAID, TIME
        FROM PICK
        JOIN USER ON PICK.USERID = USER.USERID
        JOIN SONG ON PICK.SONGID = SONG.SONGID
        JOIN KARAOKEFILE ON PICK.FILEID = KARAOKEFILE.FILEID
        WHERE PICK.QUEUETYPE = 'P'
        ");
    }
    displayQueue($premiumQueue, 'Premium');

    // query + draw the free queue
    echo "<div class=dj_if><h2>Free Queue</h2></div>";
    if (isset($_POST['sort_free'])) {

        $freeQueue = $pdo->query("
        SELECT PICK.USERID, PICK.SONGID, USER.FNAME, USER.LNAME, SONG.TITLE, SONG.ARTISTNAME, KARAOKEFILE.VERSION, TIME
        FROM PICK
        JOIN USER ON PICK.USERID = USER.USERID
        JOIN SONG ON PICK.SONGID = SONG.SONGID
        JOIN KARAOKEFILE ON PICK.FILEID = KARAOKEFILE.FILEID
        WHERE PICK.QUEUETYPE = 'F'
        ORDER BY $sort_column $sort_by;
    ");
        $_SESSION['sort_counter_prio_paid'] = 0;
        $_SESSION['sort_counter_prio_time'] = 0;

    }
    else {
            $freeQueue = $pdo->query("
            SELECT PICK.USERID, PICK.SONGID, USER.FNAME, USER.LNAME, SONG.TITLE, SONG.ARTISTNAME, KARAOKEFILE.VERSION, TIME
            FROM PICK
            JOIN USER ON PICK.USERID = USER.USERID
            JOIN SONG ON PICK.SONGID = SONG.SONGID
            JOIN KARAOKEFILE ON PICK.FILEID = KARAOKEFILE.FILEID
            WHERE PICK.QUEUETYPE = 'F'
    ");
    
    }
    displayQueue($freeQueue, 'Free');



// Function to display queues
function displayQueue($queue, $type)
{
    $rows = $queue->fetchAll(PDO::FETCH_ASSOC);
    if ($rows) {
        echo "<div class=queue><form action=dj_page.php method=POST><table>
                <tr><th>First Name</th><th>Last Name</th><th>Title</th><th>Artist</th><th>File Version</th>";
        if ($type == 'Premium') {
            echo "<th class=qsort><input type=submit value=\"Amount Paid\" name=sort_prio_paid> </th>";

        }

$sign_up_time_submit_button_name = $type == 'Free' ? 'sort_free' : 'sort_prio_time';

echo "
<th class=qsort><input type=submit value=\"Sign-up Time\" name=$sign_up_time_submit_button_name></th>
<th></th></tr></form>";
         

        foreach ($rows as $row) {
            echo "<tr>
                    <td>{$row['FNAME']}</td>
                    <td>{$row['LNAME']}</td>
                    <td>{$row['TITLE']}</td>
                    <td>{$row['ARTISTNAME']}</td>
                    <td>{$row['VERSION']}</td>";
            if ($type == 'Premium') {
                echo " <td>\${$row['PAID']}</td>";
            }
            echo "
                    <td>{$row['TIME']}</td>
                    <td>
                        <form action='' method='POST'>
                            <input type='hidden' name='user_id' value='{$row['USERID']}'>
                            <input type='hidden' name='song_id' value='{$row['SONGID']}'>
                            <button type='submit'>Remove</button>
                        </form>
                    </td>
                  </tr>";
        }
        echo "</table></div>";
    } else {
        echo "<div class=dj_if><p>No users in the {$type} queue.</p></div>";
    }
}
?>
</main>
</body>
</html>
