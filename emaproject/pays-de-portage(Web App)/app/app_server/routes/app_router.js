'use strict';

const express = require('express');
const router = express.Router();

const tourController = require('../controllers/tours');
const otherController = require('../controllers/others');


/* -- TOUR Pages -- */

/* -- GET home page -- */

router.get('/', tourController.toursList); 

/* GET the tour details page */

router.get('/details', tourController.toursDetails);

/* GET the tour reservation page */

router.get('/details/reserve-tours', tourController.reserveTours);

/* -- Other Pages -- */
/* GET about page */


router.get('/about', otherController.about);
module.exports = router;
