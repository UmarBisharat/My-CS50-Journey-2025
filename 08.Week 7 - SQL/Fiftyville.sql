-- Task 1: Select all song names
SELECT name
FROM songs;

-- Task 2: Select all unique artists
SELECT DISTINCT artist
FROM songs;

-- Task 3: Select songs from a specific year
-- Replace 2020 with the required year
SELECT name
FROM songs
WHERE year = 2020;

-- Task 4: Select songs longer than a given duration (ms)
-- Replace 200000 with the duration in milliseconds
SELECT name
FROM songs
WHERE duration_ms > 200000
ORDER BY duration_ms DESC;

-- Task 5: Top 5 songs by tempo
SELECT name
FROM songs
ORDER BY tempo DESC
LIMIT 5;

-- Task 6: Count total songs
SELECT COUNT(*) AS total_songs
FROM songs;

-- Task 7: Average danceability of songs by a specific artist
-- Replace 'Artist Name' with the artist
SELECT AVG(danceability) AS avg_danceability
FROM songs
WHERE artist = 'Artist Name';

-- Task 8: Select songs by a specific artist in a specific year
-- Replace 'Artist Name' and 2020 with actual values
SELECT name
FROM songs
WHERE artist = 'Artist Name' AND year = 2020
ORDER BY name ASC;
