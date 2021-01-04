-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT NAME FROM PEOPLE -- Output will only contain names from the "PEOPLE" table
WHERE ID IN ( -- Select only names of people if id is in the selection below

    SELECT PERSON_ID FROM DIRECTORS -- Output person ids from only directors 
    WHERE MOVIE_ID IN ( -- Select person ids if movie id is in selection below
    
        SELECT MOVIE_ID FROM RATINGS WHERE RATING >= 9.0 -- Output movie ids from movies only with ratings greater than or equal to 9.0
    
    )

);