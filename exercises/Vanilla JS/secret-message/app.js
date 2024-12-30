let secretMessage = ['Learning', 'is', 'not', 'about', 'what', 'you', 'get', 'easily', 'the', 'first', 'time,', 'it', 'is', 'about', 'what', 'you', 'can', 'figure', 'out.', '-2015,', 'Chris', 'Pine,', 'Learn', 'JavaScript'];

const removeLast = secretMessage.pop();

const addTwoNew = secretMessage.push('to', 'Program');

secretMessage[7] = 'right';

const removeFirst = secretMessage.shift();

const moveToFirst = secretMessage.unshift('Programming');

const removeExtraneousStrings = secretMessage.splice(6, 5, 'know'); 

console.log(secretMessage.join());