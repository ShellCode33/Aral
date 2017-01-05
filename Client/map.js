var colors = ["blue", "green", "yellow", "red", "orange", "white", "brown"];
var mapIsLoaded = false;
var map;
var bounds;
var boatsArray = [];
var markers = [];
var lastCalledInfoWindow = null;

qt.jQuery(function($) {
    // Asynchronously Load the map API
    var script = document.createElement('script');
    script.src = "https://maps.googleapis.com/maps/api/js?callback=initialize&key=AIzaSyBoWBTZJjAu8UYdtdMXXtHeZ8a8O5XgERs";

    if(navigator.onLine)
    {
        document.body.appendChild(script);
    }
});

//convertir couleur en code
function colourNameToHex(colour)
{
    var colours = {"aliceblue":"f0f8ff","antiquewhite":"faebd7","aqua":"00ffff","aquamarine":"7fffd4","azure":"f0ffff",
    "beige":"f5f5dc","bisque":"ffe4c4","black":"000000","blanchedalmond":"ffebcd","blue":"0000ff","blueviolet":"8a2be2","brown":"a52a2a","burlywood":"deb887",
    "cadetblue":"5f9ea0","chartreuse":"7fff00","chocolate":"d2691e","coral":"ff7f50","cornflowerblue":"6495ed","cornsilk":"fff8dc","crimson":"dc143c","cyan":"00ffff",
    "darkblue":"00008b","darkcyan":"008b8b","darkgoldenrod":"b8860b","darkgray":"a9a9a9","darkgreen":"006400","darkkhaki":"bdb76b","darkmagenta":"8b008b","darkolivegreen":"556b2f",
    "darkorange":"ff8c00","darkorchid":"9932cc","darkred":"8b0000","darksalmon":"e9967a","darkseagreen":"8fbc8f","darkslateblue":"483d8b","darkslategray":"2f4f4f","darkturquoise":"00ced1",
    "darkviolet":"9400d3","deeppink":"ff1493","deepskyblue":"00bfff","dimgray":"696969","dodgerblue":"1e90ff",
    "firebrick":"b22222","floralwhite":"fffaf0","forestgreen":"228b22","fuchsia":"ff00ff",
    "gainsboro":"dcdcdc","ghostwhite":"f8f8ff","gold":"ffd700","goldenrod":"daa520","gray":"808080","green":"008000","greenyellow":"adff2f",
    "honeydew":"f0fff0","hotpink":"ff69b4",
    "indianred ":"cd5c5c","indigo":"4b0082","ivory":"fffff0","khaki":"f0e68c",
    "lavender":"e6e6fa","lavenderblush":"fff0f5","lawngreen":"7cfc00","lemonchiffon":"fffacd","lightblue":"add8e6","lightcoral":"f08080","lightcyan":"e0ffff","lightgoldenrodyellow":"fafad2",
    "lightgrey":"d3d3d3","lightgreen":"90ee90","lightpink":"ffb6c1","lightsalmon":"ffa07a","lightseagreen":"20b2aa","lightskyblue":"87cefa","lightslategray":"778899","lightsteelblue":"b0c4de",
    "lightyellow":"ffffe0","lime":"00ff00","limegreen":"32cd32","linen":"faf0e6",
    "magenta":"ff00ff","maroon":"800000","mediumaquamarine":"66cdaa","mediumblue":"0000cd","mediumorchid":"ba55d3","mediumpurple":"9370d8","mediumseagreen":"3cb371","mediumslateblue":"7b68ee",
    "mediumspringgreen":"00fa9a","mediumturquoise":"48d1cc","mediumvioletred":"c71585","midnightblue":"191970","mintcream":"f5fffa","mistyrose":"ffe4e1","moccasin":"ffe4b5",
    "navajowhite":"ffdead","navy":"000080",
    "oldlace":"fdf5e6","olive":"808000","olivedrab":"6b8e23","orange":"ffa500","orangered":"ff4500","orchid":"da70d6",
    "palegoldenrod":"eee8aa","palegreen":"98fb98","paleturquoise":"afeeee","palevioletred":"d87093","papayawhip":"ffefd5","peachpuff":"ffdab9","peru":"cd853f","pink":"ffc0cb","plum":"dda0dd","powderblue":"b0e0e6","purple":"800080",
    "rebeccapurple":"663399","red":"ff0000","rosybrown":"bc8f8f","royalblue":"4169e1",
    "saddlebrown":"8b4513","salmon":"fa8072","sandybrown":"f4a460","seagreen":"2e8b57","seashell":"fff5ee","sienna":"a0522d","silver":"c0c0c0","skyblue":"87ceeb","slateblue":"6a5acd","slategray":"708090","snow":"fffafa","springgreen":"00ff7f","steelblue":"4682b4",
    "tan":"d2b48c","teal":"008080","thistle":"d8bfd8","tomato":"ff6347","turquoise":"40e0d0",
    "violet":"ee82ee",
    "wheat":"f5deb3","white":"ffffff","whitesmoke":"f5f5f5",
    "yellow":"ffff00","yellowgreen":"9acd32"};

    return colours[colour];
}

function initialize() {
    bounds = new google.maps.LatLngBounds();
    var mapOptions = {
        mapTypeId: 'satellite'
    };
    // Display a map on the page
    map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
    map.setTilt(45);
    map.setOptions({ minZoom: 1, maxZoom: 10 });
    mapIsLoaded = true;
    update_markers();
}

function open(boat)
{
    if(navigator.onLine)
    {
        for(i = 0; i < boatsArray.length; i++)
        {
            if(boatsArray[i][0] == boat[0])
            {
                google.maps.event.trigger(markers[i], 'click');
                break;
            }
        }
    }
}

function add_marker(boat) {
    boatsArray.push(boat);

    if(mapIsLoaded)
    {
        var pinImage = new google.maps.MarkerImage("http://chart.apis.google.com/chart?chst=d_map_pin_letter&chld=%E2%80%A2|" + colourNameToHex(colors[(boatsArray.length-1)%colors.length]),
            new google.maps.Size(21, 34),
            new google.maps.Point(0,0),
            new google.maps.Point(10, 34));
        var position = new google.maps.LatLng(boat[1], boat[2]);
        bounds.extend(position);

        markers.push(new google.maps.Marker({
             position: position,
             map: map,
             icon: pinImage,
             title: boat[0]
        }));

        var i = markers.length-1;
        // Allow each marker to have an info window
        google.maps.event.addListener(markers[i], 'click', (function(i) {
            return function() {

                if(lastCalledInfoWindow != null)
                    lastCalledInfoWindow.close();

                var str = "<h1>" + boat[0] + "</h1><br />" +
                        "<b>Latitude : </b>" + boat[1] + "<br />" +
                        "<b>Longitude : </b>" + boat[2] + "<br />" +
                        "<b>Cap : </b>" + boat[3] + "<br />" +
                        "<b>Last Time Seen : </b>" + boat[4] + "<br />";

                var infoWindow = new google.maps.InfoWindow({
                    content: str
                });

                lastCalledInfoWindow = infoWindow;

                infoWindow.open(map, markers[i]);
                throw boat;
            }
        })(i));

        map.fitBounds(bounds);
    }
}

function update_marker(boat) {

    if(navigator.onLine) {
        for(i = 0; i < boatsArray.length; i++) {
            if(boatsArray[i][0] == boat[0]) {
                //throw boatsArray[i];
                boatsArray[i][1] = boat[1];
                boatsArray[i][2] = boat[2];
                boatsArray[i][3] = boat[3];
                boatsArray[i][4] = boat[4];
                var position = new google.maps.LatLng(boatsArray[i][1], boatsArray[i][2]);
                bounds.extend(position);
                markers[i].setPosition(position)
                //map.fitBounds(bounds);
                break;
            }
        }
    }
}

function update_markers() {

    //remove all the markers
    for (var i = 0; i < markers.length; i++ ) {
        markers[i].setMap(null);
    }
    markers.length = 0;

    for(i = 0; i < boatsArray.length; i++) {
        var pinImage = new google.maps.MarkerImage("http://chart.apis.google.com/chart?chst=d_map_pin_letter&chld=%E2%80%A2|" + colourNameToHex(colors[i%colors.length]),
            new google.maps.Size(21, 34),
            new google.maps.Point(0,0),
            new google.maps.Point(10, 34));
        var position = new google.maps.LatLng(boatsArray[i][1], boatsArray[i][2]);
        bounds.extend(position);

        markers.push(new google.maps.Marker({
            position: position,
            map: map,
            icon: pinImage,
            title: boatsArray[i][0]
        }));


        // Allow each marker to have an info window
        google.maps.event.addListener(markers[i], 'click', (function(i) {
            return function() {

                if(lastCalledInfoWindow != null)
                    lastCalledInfoWindow.close();

                var str = "<h1>" + boatsArray[i][0] + "</h1><br />" +
                        "<b>Latitude : </b>" + boatsArray[i][1] + "<br />" +
                        "<b>Longitude : </b>" + boatsArray[i][2] + "<br />" +
                        "<b>Cap : </b>" + boatsArray[i][3] + "<br />" +
                        "<b>Last Time Seen : </b>" + boatsArray[i][4] + "<br />";

                var infoWindow = new google.maps.InfoWindow({
                    content: str
                });

                lastCalledInfoWindow = infoWindow;

                infoWindow.open(map, markers[i]);
            }
        })(i));
    }

    // Automatically center the map fitting all markers on the screen
    map.fitBounds(bounds);
}
