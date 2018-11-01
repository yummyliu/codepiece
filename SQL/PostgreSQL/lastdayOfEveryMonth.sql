SELECT distinct on (date_part('month',t))  date_part('month',t) as month,
       date_part('day',t) as lastday
	FROM generate_series('2018-01-01'::TIMESTAMP, '2018-03-01'::TIMESTAMP, '1 days') AS t(t)
	ORDER BY date_part('month',t),
	         date_part('day',t) DESC;

SELECT DISTINCT date_part('month',t),
                max(date_part('day',t)) over(partition BY date_part('month',t)) AS lastday
				FROM generate_series('2018-01-01'::TIMESTAMP, '2018-04-30'::TIMESTAMP, '1 days') AS t(t);
