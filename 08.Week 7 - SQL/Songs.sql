-- Question 1: Select all song names
SELECT name
FROM songs;

-- Question 2: Select all distinct artists
SELECT DISTINCT artist
FROM songs;

-- Question 3: Select songs from a specific year
-- Replace 2020 with the year required
SELECT name
FROM songs
WHERE year = 2020;

-- Question 4: Select songs longer than a certain duration (in milliseconds)
-- Replace 200000 with the duration required
SELECT name
FROM songs
WHERE duration_ms > 200000
ORDER BY duration_ms DESC;

-- Question 5: Select top 5 songs by tempo
SELECT name
FROM songs
ORDER BY tempo DESC
LIMIT 5;

-- Question 6: Count total number of songs
SELECT COUNT(*) AS total_songs
FROM songs;

-- Question 7: Average danceability of songs by a specific artist
-- Replace 'Artist Name' with the artist required
SELECT AVG(danceability) AS avg_danceability
FROM songs
WHERE artist = 'Artist Name';

-- Question 8: Select songs by a specific artist in a specific year
-- Replace 'Artist Name' and 2020 with values required
SELECT name
FROM songs
WHERE artist = 'Artist Name' AND year = 2020
ORDER BY name ASC;
