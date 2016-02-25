(function() {
	if(aeListener['indice'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;
		isInit = true;
		var myDisplay = new AEdisplay('indice-svg', SVGmodel, SVGrelations, SVGconfig);
		var stack = null;

		myDisplay.linkElement(document.querySelector('#ae-indice-cont'));
		myDisplay.prepareSvg();
		myDisplay.init();

		document.querySelector('#indice-svg').setAttribute('width', '400');
		document.querySelector('#indice-svg').setAttribute('viewBox', '0 0 400 210');

		function displayClass(cl) {
			var elems = document.querySelectorAll(cl);
			for(var i = 0; i < elems.length; ++i) {
				elems[i].style.strokeOpacity = 1;
				elems[i].style.fillOpacity = 1;
			}
		}

		myDisplay.addAction({
			'svg': {
				'showExample': [1],
				'color': '#fa8242'
			}
		});

		myDisplay.addAction({
			'svg': {
				'showExample': [2],
				'color': '#42affa'
			}
		});

		
		var receptacle = document.createElement('div');
		var svgFrag = '<svg>' + 
		'<text fill-opacity="0" class="ae-first-indice-show" x="360" y="50" fill="white" font-size="20">1 × (</text>' + 
		'<text fill-opacity="0" class="ae-first-indice-show" x="402" y="50" fill="#fa8242" font-size="20">2</text>' + 
		'<text fill-opacity="0" class="ae-first-indice-show" x="415" y="50" fill="white" font-size="20">×</text>' + 
		'<text fill-opacity="0" class="ae-first-indice-show" x="430" y="50" fill="#42affa" font-size="20">3</text>' + 
		'<text fill-opacity="0" class="ae-first-indice-show" x="445" y="50" fill="white" font-size="20">)</text>' + 

		'<text fill-opacity="0" class="ae-second-indice-show" x="395" y="105" fill="white" font-size="40">+</text>' + 

		'<text fill-opacity="0" class="ae-second-indice-show" x="374" y="140" fill="white" font-size="20">0 × (</text>' + 
		'<text fill-opacity="0" class="ae-second-indice-show" x="416" y="140" fill="#42affa" font-size="20">3</text>' + 
		'<text fill-opacity="0" class="ae-second-indice-show" x="431" y="140" fill="white" font-size="20">)</text>' + 

		'<text fill-opacity="0" class="ae-third-indice-show" x="395" y="195" fill="white" font-size="40">+</text>' + 

		'<text fill-opacity="0" class="ae-third-indice-show" x="401" y="235" fill="white" font-size="20">2</text>' + 

		'<line stroke-opacity="0" class="ae-fourth-indice-show" x1="350" y1="265" x2="470" y2="265" stroke="white"/>' + 

		'<text fill-opacity="0" class="ae-fourth-indice-show" x="401" y="310" fill="white" font-size="30">8</text>' + 

			'</svg>';
		receptacle.innerHTML = ''+svgFrag;
		Array.prototype.slice.call(receptacle.childNodes[0].childNodes).forEach(function(e) {
			document.querySelector('#indice-svg').appendChild(e);
		});

		myDisplay.nextStep();
		myDisplay.nextStep();

		myDisplay.addAction({
			'svg': {
				'showObject': [[0, 1]],
			}
		});
		myDisplay.addAction({
			'svg': {
				'showObject': [[1, 0]],
			}
		});
		myDisplay.addAction({
			'svg': {
				'showObject': [[2, 2]],
			}
		});

		var keyIndex = 0;

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['indice'].enabled == true) {
				myDisplay.nextStep();
				switch(keyIndex++) {
					case 0:
						displayClass('.ae-first-indice-show');
						break;
					case 1:
						displayClass('.ae-second-indice-show');
						break;
					case 2:
						displayClass('.ae-third-indice-show');
						break;
					case 3:
						displayClass('.ae-fourth-indice-show');
						break;
				}
			}
		});
	}

	aeListener['indice'] = {
		'disable': function() {
			aeListener['indice'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['indice'].enabled = true;
		},
		'enabled': false
	};
})();