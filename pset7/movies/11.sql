-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT TITLE AS TOP_FIVE_CHADWICK_BOSEMAN_MOVIES FROM MOVIES -- Only outputs titles from the "MOVIES" table
INNER JOIN RATINGS ON RATINGS.MOVIE_ID=MOVIES.ID
WHERE ID IN ( -- Select movie titles only if id of movie is in selection below

    SELECT MOVIE_ID FROM RATINGS -- Only outputs movie ids from the "RATINGS" table
    WHERE MOVIE_ID IN ( -- Select movie ids only if movie id is in selection below

        SELECT MOVIE_ID FROM STARS -- Only outputs movie ids from the "STARS" table
        WHERE PERSON_ID IN ( -- Select movie ids only if person id is in selection below

            SELECT ID FROM PEOPLE WHERE NAME LIKE "Chadwick Boseman" -- Select id of people with name "Chadwick Boseman"

        )

    )

) ORDER BY RATING DESC LIMIT 5; -- Limit output of only 5 rows or less and Order output by rating