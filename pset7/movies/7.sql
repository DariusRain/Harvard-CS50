-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT TITLE, RATING FROM MOVIES  -- Output is going to display title and rating of movies
INNER JOIN RATINGS -- Combine movies table with ratings table
    ON MOVIES.ID=RATINGS.MOVIE_ID -- Combine only in relation to "MOVIE_ID"
WHERE YEAR == 2010 -- Where a movie's release date is equal to 2010
ORDER BY RATING DESC, TITLE  -- Order the rows of Title alphabetically and rows of ratings descending.