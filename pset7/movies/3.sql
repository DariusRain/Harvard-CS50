-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT TITLE FROM MOVIES -- Select only title from movies
WHERE 2018 <= YEAR -- Where a movie's release year is greater than or equal to 2018
ORDER BY TITLE; -- Order movies by title in alphabetical order