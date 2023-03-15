Person = function (name, age) {
    this.name = name
    this.age = age
    this.speak = function () {
        console.log(`Im ${this.name} and i speak english`)
    }


}

Person.prototype.describe = function () {
    console.log("description")
}
Person.prototype.say = function (text) {
    console.log(`${this.name} say : ${text}`)
}



Student = function (name, age, dpt) {
    Person.call(this, name, age)

    this.dpt = dpt

    // this.getInfo = function () {
    //     console.log("=== Info ===")
    //     console.log(this.name)
    //     console.log(this.age)
    //     console.log(this.dpt)
    //     console.log("============")
    // }
}

Support = function () {
    this.constructor = Student
}

Support.prototype = Person.prototype
sup = new Support()

Student.prototype = sup

Student.prototype.study = function (studyField) {
    console.log(`I study ${studyField}`)
}

Student.prototype.getInfo = function () {
    console.log("=== Info ===")
    console.log(this.name)
    console.log(this.age)
    console.log(this.dpt)
    console.log("============")
}


let students = [
    { "name": "A", "grade": 18 },
    { "name": "B", "grade": 15 },
    { "name": "C", "grade": 5 },
]

let cb = (prev, cur) => {
    return prev + cur["grade"] / students.length
}

moy = students.reduce(cb, 0)

