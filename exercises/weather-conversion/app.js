// Constant variable for Kelvin unit.
const kelvin = 0;

// Constant variable for Celsius unit.
const celsius = kelvin - 273;

// Conversion from celsius, rounded down to the nearest integer.
let fahrenheit = Math.floor(celsius * (9/5) + 32);

console.log(`The temperature is ${fahrenheit} degrees Fahrenheit.`);

// Another conversion from celsius, rounded down.
const newton = Math.floor(celsius * (33/100));

console.log(`The temperature is ${newton} degrees Newton.`);