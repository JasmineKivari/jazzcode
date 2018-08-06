'use strict;'
const request = require('request');

const apiOptions = {
    server: 'http://192.168.99.100:3000/api'
};

if (process.env.NODE_ENV === 'production') {
    apiOptions.server =
    'http://pays-de-portage.deploy.cs.camosun.bc.ca/api';
}

const toursList = function(req, res) {
  res.render('index', { title: 'Pays De Portage', pageHeader: { title: 'Pays De Portage', tagline: 'Ride Lake Superior', sidebar: 'Pays De Portage has several portaging experiences to choose from. Please book with us to experience all Lake Superior has to offer!' }
});

};
const renderToursDetails = function(req, res, body) {
    let errorMsg = null;
    if(!(body instanceof Array)) {
        errorMsg = 'API lookup error';
         body = [];
    }
  res.render('tours-details', {tours: body,  
  title: 'Tour Details', 
  tourDetails1: 'The Thunder Bay to Pays plat round trip will portage through the traditional paths around Lake Superior', 
  tourDetails2: 'The Nipigon to Pays Plat round trip will portage 62 kilometers the traditional river trout portage paths around Lake Superior', 
  tourDetails3: 'Rossport to Pays Plat round trip will portage 9 km for the shortest portage trip, good for beginners', 
  pageHeader: { title: 'Pays De Portage', tagline: 'Choose your Portage length!'},
  errorMsg: errorMsg
    });
};

const toursDetails = function(req, res) {
  const reqOptions = {
    baseUrl: apiOptions.server,
    url: '/portages',
    method: 'GET',
    json: {}
    };
        
    request(reqOptions, function(err, apiRes, apiResBody) {
      renderToursDetails(req, res, apiResBody);
    });
};


const reserveTours = function(req, res) {
  res.render('reserve-tours',
  { title: 'Reserve a Tour', choice: 'Option 1: From Thunder Bay to Pays Plat First Nation', choice2: 'Option 2: From Nipigon to Pays Plat First Nation', choice3: 'Option 3: From Rossport to Pays Plat First Nation', pageHeader: { title: 'Pays De Portage', tagline: 'Please Reserve a Tour!'}
});
};

module.exports = {
    toursList,
    toursDetails,
    reserveTours
};
