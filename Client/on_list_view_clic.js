qt.jQuery(function($) {
    if(!navigator.onLine)
    {
        var title = document.createElement('h1');
        title.innerHTML = boat_name;

        var lati = document.createElement('p');
        lati.innerHTML = 'Latitude : ' + boat_latitude;

        var longi = document.createElement('p');
        longi.innerHTML = 'Longitude : ' + boat_longitude;

        var cap = document.createElement('p');
        cap.innerHTML = 'Cap : ' + boat_cap;

        document.getElementById('map_canvas').innerHTML = '';
        document.getElementById('map_canvas').appendChild(title);
        document.getElementById('map_canvas').appendChild(lati);
        document.getElementById('map_canvas').appendChild(longi);
        document.getElementById('map_canvas').appendChild(cap);
        mapIsLoaded = false;
    }

    else if(!mapIsLoaded)
    {
        var script = document.createElement('script');
        script.src = "https://maps.googleapis.com/maps/api/js?callback=initialize&key=AIzaSyBoWBTZJjAu8UYdtdMXXtHeZ8a8O5XgERs";
        document.body.appendChild(script);
        mapIsLoaded = true;
    }
});
