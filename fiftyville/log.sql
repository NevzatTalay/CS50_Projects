-- Keep a log of any SQL queries you execute as you solve the mystery.

--
--SELECT * FROM crime_scene_reports;

-- by doing this I have found that witnesses points out the bakery. it was on 10:15 AM.
--SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street";

-- to see what are the interviews
-- SELECT * FROM interviews

-- found the possible license plates because interviews points that time interval
--SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 25) AND activity = "exit";

--Now we can have first suspects. because we are going to relate with license plates
--SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 25) AND activity = "exit");

-- now we have to look their phone number records
--SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61;

--NOW WE KNOW THE PHONE CALLS WE NEED TO RELATE TWO RESULTS TO NARROW LIST
--SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 25) AND activity = "exit");

--ONE OF THE THIEVES IS EITHER Sofia, Diana, Kelsey or Bruce. To find out we need to know who they are calling
-- They have found manually Jack, Philip Melissa and Robin

--THE QUESTION IS WHO BOUGHT THE TICKET?

--BUT FIRST LETS TURN BACK TO ATM ISSUE.
--LETS MAKE ONE MORE MATCH WITH WITHDRAW OPERATION
--SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions  WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"));

--IT SHRINK DOWN THE SUSPECT INTO TWO. Thief is diana or bruce and helper is philip or robin.

--Now lets check their flights
--SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29;
--SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29) AND (passport_number = "3391710505" OR passport_number = "5773159633" OR passport_number = "3592750733");


--tHE PERSON WHO BOUGHT THICKET TO EARLIEST FLIGHT IS BRUCE AND HE IS TALKING TO ROBIN. THEIR FLIGHT NUMBER MATCHES WITH THE 36.
--SELECT * FROM flights WHERE id = 36;

--We can find the related city by following code.
--SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);