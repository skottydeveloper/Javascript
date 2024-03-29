require('dotenv').config();

/* 1. Install & Setup Mongoose */
const mongoose = require('mongoose');
mongoose.connect(process.env.MONGO_URI, { useNewUrlParser: true });

/* 2. Create a Model */
const Schema = mongoose.Schema;

const personSchema = new Schema({
  name: { type: String, required: true },
  age: Number,
  favoriteFoods: [String]
});

/* 3. Create and Save a Record of a Model */
const Person = mongoose.model('Person', personSchema);

const createAndSavePerson = function(done) {
  const person = new Person({name: "Steve", age: 57, favoriteFoods: ["meat", "yogurt", "vegetables"]});

  person.save(function(err, data) {
    if (err) return console.error(err);
    done(null, data)
  });
};

/* 4. Create Many Records with 'model.create()' */
const arrayOfPeople = [
  {name: "Andreas", age: 21, favoriteFoods: ["Spaghetti Bolognese"]},
  {name: "Fernando", age: 41, favoriteFoods: ["Pizza"]},
  {name: "Lewis", age: 38, favoriteFoods: ["Stir-fried Vegetable Dish"]}
];

const createManyPeople = function(arrayOfPeople, done) {
  Person.create(arrayOfPeople, function(err, people) {
    if (err) return console.log(err);
    done(null, people);
  });
};

/* 5. 'Use model.find()' to Search Your Database */
const findPeopleByName = function(personName, done) {
  Person.find({name: personName}, function(err, personFound) {
    if (err) return console.log(err);
    done(null, personFound);
  });
};

/* 6. Use 'model.findOne()' to Return a Single Matching Document from Your Database */
const findOneByFood = function(food, done) {
  Person.findOne({favoriteFoods: food}, function(err, data) {
    if (err) return console.log(err);
    done(null, data);
  });
};

/* 7. Use 'model.findById()' to Search Your Database By '_id' */
const findPersonById = function(personId, done) {
  Person.findById(personId, function(err, data) {
    if (err) return console.log(err);
    done(null, data);
  });
};

/* 8. Perform Classic Updates by Running Find, Edit, then Save */
const findEditThenSave = (personId, done) => {
  const foodToAdd = 'bacon';

  Person.findById(personId, (err, person) => {
    if(err) return console.log(err); 
  
    person.favoriteFoods.push(foodToAdd);

    person.save((err, updatedPerson) => {
      if(err) return console.log(err);
      done(null, updatedPerson);
    });
  });
};

/* 9. Perform New Updates on a Document Using 'model.findOneAndUpdate()' */
const findAndUpdate = (personName, done) => {
  const ageToSet = 20;

  Person.findOneAndUpdate({name: personName}, {age: ageToSet}, {new: true}, (err, updatedDoc) => {
    if(err) return console.log(err);
    done(null, updatedDoc);
  })
};

/* 10. Delete One Document Using 'model.findByIdAndRemove()' */
const removeById = function(personId, done) {
  Person.findByIdAndRemove(personId, (err, removedDoc) => {
    if(err) return console.log(err);
    done(null, removedDoc);
  }); 
};

/* 11. Delete Many Documents with 'model.remove()' */
const removeManyPeople = (done) => {
  const nameToRemove = "Lewis";

  Person.remove({name: nameToRemove}, (err, response) => {
    if(err) return console.log(err);
    done(null, response);
  })
};

/* 12. Chain Search Query Helpers to Narrow Search Results */
const queryChain = (done) => {
  const foodToSearch = "Pizza";

  Person.find({ favoriteFoods: foodToSearch })
    .sort('name')
    .limit(5)
    .select(['name', 'favouriteFoods'])
    .exec((err, data) => {
      if (err) return console.log(err);
      done(err, data);
    });
};

//----- **DO NOT EDIT BELOW THIS LINE** ----------------------------------

exports.PersonModel = Person;
exports.createAndSavePerson = createAndSavePerson;
exports.findPeopleByName = findPeopleByName;
exports.findOneByFood = findOneByFood;
exports.findPersonById = findPersonById;
exports.findEditThenSave = findEditThenSave;
exports.findAndUpdate = findAndUpdate;
exports.createManyPeople = createManyPeople;
exports.removeById = removeById;
exports.removeManyPeople = removeManyPeople;
exports.queryChain = queryChain;
