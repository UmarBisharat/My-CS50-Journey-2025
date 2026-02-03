-- Movies – CS50 2025 Pset 7
-- One query per question. End each query with a semicolon.

-- Task 1: Select all movie titles
SELECT title
FROM movies;

-- Task 2: Select all distinct directors
SELECT DISTINCT director
FROM movies;

-- Task 3: Select movies released in a specific year
-- Replace 2020 with the year required
SELECT title
FROM movies
WHERE year = 2020;

-- Task 4: Select movies longer than a certain duration (in minutes)
-- Replace 120 with the duration required
SELECT title
FROM movies
WHERE duration_min > 120
ORDER BY duration_min DESC;

-- Task 5: Top 5 movies by rating
-- Replace 'rating' with the actual column if needed
SELECT title
FROM movies
ORDER BY rating DESC
LIMIT 5;

-- Task 6: Count total number of movies
SELECT COUNT(*) AS total_movies
FROM movies;

-- Task 7: Average rating of movies by a specific director
-- Replace 'Director Name' with the actual director
SELECT AVG(rating) AS avg_rating
FROM movies
WHERE director = 'Director Name';

-- Task 8: Select movies by a specific director in a specific year
-- Replace 'Director Name' and 2020 with actual values
SELECT title
FROM movies
WHERE director = 'Director Name' AND year = 2020
ORDER BY title ASC;
