-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT COUNT(DISTINCT MOVIE_ID) AS RESULT -- Select the number of movies from selection
FROM RATINGS WHERE RATING == 10.0; -- Where a movie's rating is equal to 10.0