-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT TITLE AS MOVIES_WITH_JOHNNY_DEPP_AND_HELENA_BONHAM_CARTER FROM MOVIES -- Outputs titles from "MOVIES TABLE"
INNER JOIN STARS -- Combine both "STARS" and "MOVIES" table
    ON STARS.MOVIE_ID=MOVIES.ID -- Combine with relation to movie ids
INNER JOIN PEOPLE -- Combine both "PEOPLE" and "MOVIES" tables
    ON PEOPLE.ID = STARS.PERSON_ID -- Combine with relation to person ids
WHERE NAME LIKE "Johnny Depp" OR NAME LIKE "Helena Bonham Carter" -- Select name from combined table where name is equal to either name
GROUP BY TITLE -- Group all findings by title
HAVING COUNT(*)=2; -- where title has count of two (Represents movies where both names are starred in)