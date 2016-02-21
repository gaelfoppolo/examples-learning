(function() {
	if(aeListener['generation'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;
		isInit = true;
		var myEngine = new AEengine(SVGmodel);
		var myDisplay = new AEdisplay('generation-svg', SVGmodel, SVGrelations, SVGconfig);
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
				'text': stack
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

		myDisplay.linkElement(document.querySelector('#ae-generation-cont'));
		myDisplay.prepareSvg();
		myDisplay.prepareTable();
		myDisplay.init();
		myEngine.run();

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['generation'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

		

	aeListener['generation'] = {
		'disable': function() {
			aeListener['generation'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['generation'].enabled = true;
			console.log('initialisé');
		},
		'enabled': false
	};
})();