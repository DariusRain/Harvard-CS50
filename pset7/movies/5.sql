-- https://cs50.harvard.edu/x/2020/psets/7/movies/#specification
SELECT TITLE, YEAR FROM MOVIES -- Select only title and year from movies where output will be two columns
WHERE (lower(title) LIKE 'harry potter%') -- Where if title case with insensitivity begins with "harry potter" 
ORDER BY YEAR; -- Order the outputted table by year of each harry potter movie found