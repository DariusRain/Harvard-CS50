-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT NAME FROM PEOPLE -- Output will only contain names from "PEOPLE" table
WHERE ID IN ( -- Select names of people only if id is in the selection below

    SELECT DISTINCT PERSON_ID FROM STARS -- Output only person ids from stars (No duplicates)
    WHERE MOVIE_ID IN ( -- Select person ids only if movie_id is in the selection below

        SELECT ID FROM MOVIES WHERE YEAR=2004 -- Output all movie ids from movies released in 2004

    )

)
ORDER BY BIRTH -- Order all people by birth year;