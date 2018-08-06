'use strict';

const express = require('express');
const router = express.Router();

const portagesAPIController = require('../controllers/portages-api');
const portageTimesAPIController = require('../controllers/portages-times-api');

/*-- portages --*/
router
  .route ('/portages')
  
  .get(portagesAPIController.portagesListByOrigin);
  
 // .post(portagesAPIController.portagesCreate);
 
 /*-- portage times -- */
router
  .route('/portages/:portageid')
  
  .get(portageTimesAPIController.portageTimesReadOne);
   
module.exports = router;