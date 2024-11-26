var userName = '';

userName ? console.log(`Hello, ${userName}!`) : console.log('Hello!');

const userQuestion = 'Will I have a good day today?';

userName ? console.log(`${userName}, you have asked: ${userQuestion}`) : console.log(`You have asked: ${userQuestion}`); 

const randomNumber = Math.floor(Math.random() * 8);

let eightBall = '';

switch (randomNumber) {
  case 0:
    console.log('It is certain.');
    break;
  case 1:
    console.log('It is decidedly so.');
    break;
  case 2:
    console.log('Reply hazy. Try again.');
    break;
  case 3:
    console.log('Cannot predict now.');
    break;
  case 4:
    console.log('Do not count on it.');
    break;
  case 5:
    console.log('My sources say no.');
    break;
  case 6:
    console.log('Outlook not so good.');
    break;
  case 7:
    console.log('Signs point to yes.');
    break;
  default:
    console.log('Error.');
    break;
}

console.log(eightBall);