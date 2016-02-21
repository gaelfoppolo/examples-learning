(function() {
	if(aeListener['generalisation'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;


		var linkTo = [
			['001', 4],
			['010', 1],
			['011', 1],
			['012', 1],
			['100', 7],
			['101', 10],
			['102', 6],
			['110', 10],
			['200', 6],
			['201', 6],
			['210', 9],
			['211', 10]
		];


		isInit = true;
		var myEngine = new AEengine(SVGmodel);
		var myDisplay = new AEdisplay('generalisation-svg', SVGmodel, SVGrelations, SVGconfig);
		var stack = null;

		myEngine.on('new-example', function(e) {
			myDisplay.addAction({
				'svg': {
					'showExample': [e.example]
				}
			});
		});

		myEngine.on('end-example', function(e) {
			myDisplay.addUnaction({
				'svg': {
					'showExample': [e.example]
				}
			});
		});

		myEngine.on('new-object', function(e) {
			myDisplay.addAction({
				'svg': {
					'showObject': [[e.example, e.object]]
				}
			});
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
			myDisplay.addUnaction({
				'svg': {
					'showObject': [[e.example, e.object]]
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

		myDisplay.linkElement(document.querySelector('#ae-generalisation-cont'));
		myDisplay.prepareSvg();
		myDisplay.prepareTable();
		myDisplay.init();
		myEngine.run();

		for(var i = 0; i < 40; ++i) {
			myDisplay.nextStep();
		}

		for(var i = 0; i < linkTo.length; ++i) {
			myDisplay.addAction({
				'relation': {
					'index': linkTo[i][0],
					'value': linkTo[i][1]
				}
			});
			myDisplay.addUnaction({
				'back': {
					example: linkTo[i][0]
				}
			});
		}

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['generalisation'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

	aeListener['generalisation'] = {
		'disable': function() {
			aeListener['generalisation'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['generalisation'].enabled = true;
		},
		'enabled': false
	};
})();