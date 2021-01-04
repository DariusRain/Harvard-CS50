-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT NAME AS TOY_STORY_STARS FROM PEOPLE -- Output will only have names from "PEOPLE" table
WHERE ID IN ( -- Select only names of people if a person's ID is in the below selection

    SELECT PERSON_ID FROM STARS -- Select only ids of people from stars
    WHERE MOVIE_ID=(SELECT ID FROM MOVIES WHERE TITLE LIKE "Toy Story") -- Where movie's id is Toy Story's 

);