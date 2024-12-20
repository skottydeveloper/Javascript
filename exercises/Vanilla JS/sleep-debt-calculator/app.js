const getSleepHours = day => {
    if (day === 'Monday') {
        return 8;
    } else if (day === 'Tuesday') {
        return 7;
    } else if (day === 'Wednesday') {
        return 8;
    } else if (day === 'Thursday') {
        return 7;
    } else if (day === 'Friday') {
        return 6;
    } else if (day === 'Saturday') {
        return 6;
    } else if (day === 'Sunday') {
        return 8;
    } else {
        return 'Invalid day!';
    }
};

const getActualSleepHours = () => {
    const mon = getSleepHours('Monday');
    const tue = getSleepHours('Tuesday');
    const wed = getSleepHours('Wednesday');
    const thu = getSleepHours('Thursday');
    const fri = getSleepHours('Friday');
    const sat = getSleepHours('Saturday');
    const sun = getSleepHours('Sunday');

    return mon + tue + wed + thu + fri + sat + sun;
};

const getIdealSleepHours = () => {
    const idealHours = 7.5;

    return idealHours * 7;
};

const calculateSleepDebt = () => {
    const actualSleepHours = getActualSleepHours();
    const idealSleepHours = getIdealSleepHours();

    if (actualSleepHours === idealSleepHours) {
        console.log("You got a perfect amount of sleep!");
    } else if (actualSleepHours > idealSleepHours) {
        console.log(`You got more sleep than needed! Hours over: ${actualSleepHours - idealSleepHours}`);
    } else {
        console.log(`Get some more rest! Hours under: ${idealSleepHours - actualSleepHours}`);
    }
}

calculateSleepDebt();