(function() {
	if(aeListener['generalization'] != null) return;

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
		var myDisplay = new AEdisplay('generalization-svg', SVGmodel, SVGrelations, SVGconfig);
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

		myDisplay.linkElement(document.querySelector('#ae-generalization-cont'));
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

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['generalization'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

	aeListener['generalization'] = {
		'disable': function() {
			aeListener['generalization'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['generalization'].enabled = true;
		},
		'enabled': false
	};
})();