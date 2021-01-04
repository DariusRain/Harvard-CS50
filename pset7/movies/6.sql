-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT AVG(RATING)-- The output is going to be one column with division of sum by count of ratings (Average)
AS AVERAGE -- Represent the table header by naming it as "AVERAGE"
FROM RATINGS
INNER JOIN MOVIES ON MOVIES.ID=RATINGS.MOVIE_ID -- Combine movies together to get movie year
WHERE YEAR = 2012; -- Get only movies released in 2012