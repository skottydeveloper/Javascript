// My age as a constant.
const myAge = 22;

// A variable for calculating a dog's age, at 2 human years.
let earlyYears = 2;

earlyYears *= 10.5;

// We have already accounted for the first two years.
let laterYears = myAge - 2;

// Calculate the number of dog years after first two years.
laterYears *= 4;

// The final calculation for the dog's age.
const myAgeInDogYears = earlyYears + laterYears;

// Put name in lowercase.
const myName = "Andreas".toLowerCase();

console.log(`My name is ${myName}. I am ${myAge} years old in human years which is ${myAgeInDogYears} years old in dog years.`);