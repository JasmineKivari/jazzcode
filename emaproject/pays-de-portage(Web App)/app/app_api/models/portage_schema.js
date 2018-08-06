const mongoose = require('mongoose');


const portageTimeSchema = new mongoose.Schema({
    
    depart: String,
    arrive: String,
    portageNum: Number,
    Fare: String
});
const portageSchema = new mongoose.Schema({
    origin: {
        type: String,
        required: true,
        enum: ['Thunder Bay', 'Nipigon', 'Rossport', 'Pays Plat']
    },
    destination: {
        type: String,
        required: true,
        enum: ['Thunder Bay', 'Nipigon', 'Rossport', 'Pays Plat']
    },
    days: [String],
    portageTimes: [portageTimeSchema],
    portageDates: {
        type: [Date],
        default: Date(),
        min: Date(),
        max: Date (new Date().setFullYear(new Date().getFullYear() +1))
    }, 
    rating: {
        type: Number,
        default: 0,
        min: 0,
        max: 5
    }
 
});

mongoose.model('portage', portageSchema);