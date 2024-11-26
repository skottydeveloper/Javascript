let raceNumber = Math.floor(Math.random() * 1000);

const isEarly = true;

const age = 18;

isEarly && age ? raceNumber += 1000 : raceNumber;

if (isEarly && age > 18) {
  console.log(`Runner number ${raceNumber}, you'll be racing at 9:30am.`);
} else if (!isEarly && age > 18) {
  console.log(`Runner number ${raceNumber}, you'll be racing at 11am.`);
} else if (age < 18) {
  console.log(`Runner number ${raceNumber}, you'll be racing at 12:30am.`);
} else {
  console.log('Please see the registration desk.');
}