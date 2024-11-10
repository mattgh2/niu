---------------------------------------------------------
--                                                     --
--              Author:      Matt Warner               --
--              Section No:  0001                      --
--                                                     --
--                                                     --
---------------------------------------------------------

-- 1 -- (List authors first and last name ordered by first name.
SELECT AuthorFirst, AuthorLast 
    FROM Author 
    ORDER BY AuthorFirst;

-- 2 -- (List all of the cities that have a publisher located in them. List each of the appropriate cities only once.)
SELECT DISTINCT city FROM Publisher;

-- 3 -- (Show how many books exist in the database)
SELECT COUNT(BookCode) FROM Book;

-- 4 -- (List the names of all of the branches along with the total number of books on hand at each of those branches.)
SELECT BranchName, SUM(onHand) 
    FROM Branch, Inventory 
    WHERE Branch.BranchNum = Inventory.BranchNum 
    GROUP BY BranchName;

-- 5 -- (Show the number of employees that work at Henry Books.)
SELECT SUM(NumEmployees) FROM Branch;

-- 6 -- (List the titles of all of the books written by Stephen King.)
SELECT Title
    FROM Book, Wrote, Author 
    WHERE Wrote.AuthorNum = Author.AuthorNum
        AND Book.BookCode = Wrote.BookCode
        AND AuthorFirst = 'Stephen';

-- 7 -- (List the title, type and price for all of the paperback books.)
SELECT Title, Type, Price
    FROM Book
    Where Paperback = 'Y';

-- 8 -- (Show the names of all of the branches that have at least one book with ten or more copies on hand.)
SELECT BranchName, SUM(OnHand)
    FROM Branch, Inventory
    WHERE Branch.BranchNum = Inventory.BranchNum
    GROUP BY BookCode
    HAVING SUM(OnHand) >= 10;

-- 9 -- List the title and the full name of the author for each book in reverse alphabetical order by title.
SELECT Title, AuthorFirst, AuthorLast
    FROM Book, Author, Wrote
    WHERE Author.AuthorNum = Wrote.AuthorNum
        AND Book.BookCode = Wrote.BookCode
    ORDER BY Title DESC;

-- 10 -- List all of publishers by name, along with how many books each of those publishers has published.
SELECT PublisherName, COUNT(BookCode)
    FROM Publisher, Book
    WHERE Book.PublisherCode = Publisher.PublisherCode
    GROUP BY PublisherName;

-- 11 -- (Show the number of books that cost less than $10.00.)
SELECT COUNT(Price) AS 'under $10.00'
    FROM Book
    WHERE Price < 10;

-- 12 -- (List the last name for all of the authors published by Simon and Schuster.)
SELECT AuthorLast 
    FROM Book, Author, Wrote, Publisher
    WHERE Author.AuthorNum = Wrote.AuthorNum
        AND Book.BookCode = Wrote.BookCode
        AND Publisher.PublisherCode = Book.PublisherCode
        AND Publisher.PublisherName = 'Simon and Schuster';
        
-- 13 -- (Show a list with all the types of books and how many books there are for each of them.)
SELECT Type, COUNT(Type)
    FROM Book
    GROUP BY Type;

-- 14 -- (UUShow the number of books on hand at the Brentwood Mall location.)
SELECT SUM(OnHand) FROM Inventory, Branch
    WHERE Inventory.BranchNum = Branch.BranchNum
        AND BranchLocation = 'Brentwood Mall';

-- 15 -- (List all of the branch locations along with the number of employees and the number of books on hand at each of those branches.
SELECT BranchLocation, SUM(NumEmployees), SUM(OnHand)
    FROM Inventory, Branch
    WHERE Inventory.BranchNum = Branch.BranchNum
    GROUP BY BranchLocation;

-- 16 -- (List the titles of all of the books which have a sequence number of one. Use a subquery to do it.)
SELECT Title FROM Book WHERE BookCode IN (
    SELECT BookCode FROM Wrote
    WHERE Sequence = 1
);
-- 17 -- (List all of the publishers whose name begins with “T”.)
SELECT PublisherName
    FROM Publisher
    WHERE PublisherName LIKE 'T%';

--18-- (UUList all of the information pertaining to authors that have a double-L in their name (“ll”).)
SELECT * FROM Author
    WHERE AuthorFirst OR AuthorLast LIKE '%ll%';

-- 19 -- (List all of the book titles that have a book code of 079x, 138x, or 669x.)
SELECT Title FROM Book
    WHERE BookCode LIKE '%x';

-- Alternative way
SELECT Title FROM Book
    WHERE BookCode = '079x' OR BookCode = '138x' OR BookCode = '669x';

-- 20 -- (Show the titles of all the books, along with their author’s last name and the name of the publisher, sorted in alphabetical order by the publisher’s)
SELECT Title, AuthorLast, PublisherName
    FROM Book, Wrote, Author, Publisher
    WHERE Book.BookCode = Wrote.BookCode
        AND Author.AuthorNum = Wrote.AuthorNum
        AND Publisher.PublisherCode = Book.PublisherCode
    ORDER BY PublisherName;

-- 21 -- (Do any two of the above items again, accomplishing the task in a different way. (Different SQL for same result.) Make sure to identify which items you are doing again.)

-- Task (19) (List all of the book titles taht have a book code of 079x, 138x, 669x).
SELECT Title FROM Book
    WHERE BookCode = '079x' OR BookCode = '138x' OR BookCode = '669x';

-- Task (17) Displaying publishers whose name starts with "T" 
SELECT PublisherName
FROM Publisher
WHERE SUBSTRING(PublisherName, 1, 1) = 'T';


-- 22 -- (By examining the tables, (you, not the script) determine another type of information that would be of interest to a person that worked at Henry Books. Indicate what you chose and provide the query.)

-- Query that lists all the titles that are horror at each of the branch locations and gives the amount on hand at each loaction.
SELECT BranchName, OnHand, Title, Type
    FROM Branch, Inventory, Book
    WHERE Branch.BranchNum = Inventory.BranchNum
        AND Book.BookCode = Inventory.BookCode
        AND Type = 'HOR';
