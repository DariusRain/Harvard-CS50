-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT DISTINCT NAME AS STARS_WITH_KEVIN_BACON FROM PEOPLE -- Outputs only names from the "PEOPLE" table
WHERE ID IN ( -- Select ids only found in selection below

    SELECT PERSON_ID FROM STARS -- Outputs only person ids from the "STARS" table
    WHERE MOVIE_ID IN ( -- Select movie ids only found in selection below

        SELECT MOVIE_ID FROM STARS -- Outputs only movie ids from the "STARS TABLE"
        WHERE PERSON_ID=(
            SELECT ID FROM PEOPLE -- Outputs ids (Only one id is expected) from the "PEOPLE" table
            WHERE NAME LIKE "Kevin Bacon" and birth=1958 -- Only select id of people with this name and birth year
        )

    )

)
AND NAME NOT IN ("Kevin Bacon") -- Exclude name used in query from the outputted table of names.