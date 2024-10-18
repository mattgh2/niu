-- (1) && (2) --
USE BabyName;
show tables;

-- (3) --
SELECT DISTINCT name FROM BabyName WHERE year = '2003';

-- (4) --
DESCRIBE BabyName;

-- (5) --
SELECT place, COUNT(DISTINCT name) from BabyName GROUP BY place;

-- (6) -- 
SELECT DISTINCT year FROM BabyName WHERE name = 'matt';

-- (7Where) --
SELECT name, count(name) * count AS `Frequency`
    FROM BabyName
    WHERE year = '1984'
    GROUP BY name
    ORDER BY `Frequency` DESC
    LIMIT 1;

-- (8) --
SELECT * from BabyName WHERE name LIKE 'm___' ORDER BY name, count, year;

-- (9) --
SELECT COUNT(DISTINCT name) FROM BabyName WHERE year = '1949';

-- (10) --
SELECT COUNT(*) AS `Rows in Table` FROM BabyName;

-- (11) --
SELECT gender, COUNT(name) FROM BabyName WHERE year = '1973' GROUP BY gender;

-- (12) -- 
SELECT DISTINCT substr(name, 1,1) AS `First Letter`, COUNT(DISTINCT name) AS `Frequency` FROM BabyName GROUP BY substr(name,1,1);
