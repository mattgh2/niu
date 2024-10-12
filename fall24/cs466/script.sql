DROP TABLE IF EXISTS Visit;
DROP TABLE IF EXISTS Dog;

CREATE TABLE Dog (
    dog_id SMALLINT UNSIGNED AUTO_INCREMENT,
    breed VARCHAR(20),
    name VARCHAR(20),
    weight FLOAT,
    
    PRIMARY KEY (dog_id)
);

INSERT INTO Dog (breed, name, weight)
    VALUES('Bulldog', 'Edward', 225);

INSERT INTO Dog (breed, name, weight)
    VALUES('Foxhound', 'Gerald', 50);

INSERT INTO Dog (breed, name, weight)
    VALUES('Basenji', 'Richard', 30);

INSERT INTO Dog (breed, name, weight)
    VALUES('Huskie', 'Jason', 32);

INSERT INTO Dog (breed, name, weight)
    VALUES('German Shepard', 'Scott', 39);

INSERT INTO Dog (breed, name, weight)
    VALUES('Giant Schnauzer', 'Sean', 100);

DESCRIBE Dog;

SELECT * FROM Dog;

CREATE TABLE Visit (
    visit_id SMALLINT UNSIGNED AUTO_INCREMENT,
    dog_id SMALLINT UNSIGNED NOT NULL,
    location VARCHAR(20),
    visit_date DATE,
    visit_duration TIME,
    
    PRIMARY KEY (visit_id),
    FOREIGN KEY (dog_id) REFERENCES Dog(dog_id)
);

INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(1, 'France', '2012-06-21', 22);
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(2, 'Paris', '2013-07-21', '01:16:00');
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(3, 'Latvia', '2015-12-25', 45);
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(4, 'Spain', '2015-01-29', 59);
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(5, 'Russia', '2012-06-21', 2000);
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(6, 'United States', '2012-06-21', '01:15:00');
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(1, 'Germany', '2012-07-21', '01:30:00');
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(2, 'Austria', '2012-05-21', '01:30:00');
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(3, 'South Africa', '2011-06-21', 20000);
INSERT INTO Visit (dog_id, location, visit_date, visit_duration)
    Values(4, 'France', '2012-06-21', '03:10:00');

DESCRIBE Visit;
SELECT * FROM Visit;

ALTER TABLE Visit ADD visit_cost DECIMAL(5,2) UNSIGNED DEFAULT 0;

UPDATE Visit
    -- Cost is 100 dollars per hour.
    SET visit_cost = 100 * (visit_duration / 10000)

    WHERE visit_duration > 10000;

SELECT * FROM Visit;
