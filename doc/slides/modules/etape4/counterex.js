(function() {
	if(aeListener['counterex'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;


		var linkTo = [
			['001', 4, "#42affa"],
			['010', 4, "#42affa"],
			['011', 7, "#42affa"],
			['012', 2, "#fa8242"],
			['100', 7, "#42affa"],
			['101', 10, "#42affa"],
			['102', 7, "#42affa"],
			['110', 10, "#42affa"],
			['200', 10, "#42affa"],
			['201', 10, "#42affa"],
			['210', 10, "#42affa"],
			['211', 10, "#42affa"]
		];

		isInit = true;
		var myEngine = new AEengine(SVGmodel);
		var myDisplay = new AEdisplay('counterex-svg', SVGmodel, SVGrelations, SVGconfig);
		var stack = null;


		myEngine.on('new-object', function(e) {
			stack = {};
		});

		myEngine.on('end-object', function(e) {
			myDisplay.addAction({
				'text': stack,
				'back': {
					'example': e.example,
					'object': e.object
				}
			});
		});

		myEngine.on('combi-line', function(e) {
			stack[e.index] = {
				size: e.value.inter.min + ' -> ' + e.value.inter.max,
				color: e.value.color,
				shape: e.value.shape,
			}
		});

		myDisplay.linkElement(document.querySelector('#ae-counterex-cont'));
		myDisplay.prepareSvg();
		myDisplay.prepareTable();
		myDisplay.init();
		document.querySelector('#counterex-svg').innerHTML = '';
		
		var receptacle = document.createElement('div');
		var svgFrag = '<svg>' + '<polygon points="0,80 0,180 100,180 100,80" fill="' + SVGconfig.colors.bleu + '" />' +
			'<text x="50" y="140" fill="hsl(0, 0%, 13%)" font-size="25" text-anchor="middle">3</text>' + 
			'</svg>';
		receptacle.innerHTML = ''+svgFrag;
		Array.prototype.slice.call(receptacle.childNodes[0].childNodes).forEach(function(e) {
			document.querySelector('#counterex-svg').appendChild(e);
		});


		myEngine.run();

		for(var i = 0; i < linkTo.length; ++i) {
			myDisplay.addAction({
				'relation': {
					'index': linkTo[i][0],
					'value': linkTo[i][1],
					'color': linkTo[i][2]
				}
			});
			myDisplay.addUnaction({
				'back': {
					example: linkTo[i][0]
				}
			});
		}

		for(var i = 0; i < 60; ++i) {
			myDisplay.nextStep();
		}

		myDisplay.addUnaction({
			'back': {
				example: '202'
			}
		});
		myDisplay.addUnaction({
			'back': {
				example: '212'
			}
		});

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['counterex'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

	aeListener['counterex'] = {
		'disable': function() {
			aeListener['counterex'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['counterex'].enabled = true;
		},
		'enabled': false
	};
})();