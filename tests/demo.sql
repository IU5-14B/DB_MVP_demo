CREATE DATABASE demo;
CREATE TABLE users (id INT, name VARCHAR(50), age INT, rating FLOAT, active BOOL);
INSERT INTO users VALUES (1, 'Alice', 20, 4.5, TRUE), (2, 'Bob', 25, 3.7, FALSE), (3, 'Carol', 30, 4.9, TRUE);
SELECT * FROM users;
SELECT name, age FROM users WHERE active = TRUE AND age >= 20;
UPDATE users SET rating = 5.0 WHERE name = 'Alice';
SELECT id, name, rating FROM users WHERE rating >= 4.8;
DELETE FROM users WHERE active = FALSE OR age < 21;
SELECT * FROM users;
