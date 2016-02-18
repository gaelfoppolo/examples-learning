(function() {
	if(aeListener['workflow'] != null) return;

	aeListener['workflow'] = {
		'disable': function() {
		},
		'enable': function() {
			// start the animation
			console.log('start animation');
			document.querySelector('#workflow-anim-cont').beginElement();
		}
	};
})();