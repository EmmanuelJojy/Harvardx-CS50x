SELECT name FROM movies
JOIN stars ON stars.movie_id == movies.id
JOIN people ON people.id == stars.person_id
WHERE stars.movie_id IN

(SELECT stars.movie_id FROM stars
JOIN people ON people.id == stars.person_id
WHERE people.name == "Kevin Bacon"
AND people.birth == 1958)

AND name != "Kevin Bacon"

GROUP BY people.id;