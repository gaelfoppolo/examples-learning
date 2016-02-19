var genSVG = null;
(function() {
	if(genSVG != null) return;

	function genCoords(offset, size, pos) {
		return pos * size + offset;
	}

	function genShapeValue(item, offsetX, offsetY, width, height, color) {
		var res = item.item;
		for (var i in item) {
			if (item.hasOwnProperty(i) && i != 'item') {
				if (i[0] == '-') {
					// pas d'offset
					offsetX = 0;
					offsetY = 0;
				}
				var dim = (i.indexOf('y') != -1 ? height : width);
				var offset = (i.indexOf('y') != -1 ? offsetY : offsetX);
				res = res.replace('%' + i, dim * parseFloat(item[i]) + offset);
			}
		}
		return res.replace('%color', color);
	}

	function genTextValue(text, offsetX, offsetY, x, y, fontSize, color) {
		return '<text x="' + (offsetX + x) + '" y="' + (offsetY + y + 0.3 * fontSize) + '" fill="' + color + '" font-size="' + fontSize + '" text-anchor="middle">' + text + '</text>';
	}

	function genRelation(text, offsetX, offsetY, objInterX, textConfig, lineConfig) {
		return '<line x1="' + offsetX + '" y1="' + offsetY + '" x2="' + (offsetX + objInterX - 5) + '" y2="' + offsetY + '" stroke="' + lineConfig.color + '" stroke-width="' + lineConfig.size + '" />' +
			'<polygon points="' + (offsetX + objInterX) + ',' + offsetY + ' ' + (offsetX + objInterX - 5) + ',' + (offsetY - 5) + ' ' + (offsetX + objInterX - 5) + ',' + (offsetY + 5) + '" fill="' + lineConfig.color + '" />' +
			genTextValue(text, offsetX, offsetY, 0.5 * objInterX, -0.6 * textConfig.size, textConfig.size, textConfig.color);
	}

	function genSeparator(offsetY, width, separatorConfig) {
		return '<line x1="0" y1="' + offsetY + '" x2="' + width + '" y2="' + offsetY + '" stroke="' + separatorConfig.color + '" stroke-width="' + separatorConfig.size + '" />';
	}

	function genExId(index, offsetX, offsetY, fontConfig, circleConfig) {
		return '<circle cx="' + offsetX + '" cy="' + offsetY + '" r="' + circleConfig.radius + '" stroke="' + circleConfig.color + '" stroke-width="' + circleConfig.size + '" fill-opacity="0"/>' +
			'<text x="' + offsetX + '" y="' + (offsetY + 0.3 * fontConfig.size) + '" fill="' + fontConfig.color + '" font-size="' + fontConfig.size + '" text-anchor="middle">' + index + '</text>';
	}

	function genExBorder(className, index, offsetX, offsetY, width, height, borderConfig) {
		return '<rect class="' + genClassName(className, {
			'id': index
		}) + '" x="' + offsetX + '" y="' + offsetY + '" width="' + width + '" height="' + height + '" stroke="' + borderConfig.color + '" stroke-width="' + borderConfig.size + '" fill-opacity="0" stroke-opacity="0"/>';
	}

	function genObjBorder(className, exIndex, objIndex, offsetX, offsetY, objectConfig, borderConfig) {
		return '<rect class="' + genClassName(className, {
			'ex': exIndex,
			'obj': objIndex
		}) + '" x="' + offsetX + '" y="' + offsetY + '" width="' + objectConfig.width + '" height="' + objectConfig.height + '" stroke="' + borderConfig.color + '" stroke-width="' + borderConfig.size + '" fill-opacity="0" stroke-opacity="0"/>';
	}

	function genClassName(className, items) {
		var ret = '';
		for (var i = 0; i < className.length; ++i) {
			var current = className[i];
			for (var j in items) {
				current = current.replace('%' + j, '' + items[j]);
			}
			ret += ' ' + current + ' ';
		}
		return ret;
	}

	genSVG = function(element, id, config, model, relations) {
		var svgContent = '';
		var maxObjLength = 0;

		for (var i = 0; i < model.length; ++i) {
			if (model[i].length > maxObjLength) {
				maxObjLength = model[i].length;
			}
		}

		var width = (config.margins.left + config.margins.right + maxObjLength * config.object.width + (maxObjLength - 1) * config.margins['hori-objects']);
		var height = (config.margins.top + config.margins.bottom + model.length * config.object.height + (model.length - 1) * config.margins['verti-objects']);

		for (var i = 0; i < model.length; ++i) {

			// génération du séparateur
			if (i != model.length - 1) {
				svgContent += '\n' + genSeparator(config.margins.top + (i + 1) * config.object.height + (i + 0.5) * config.margins['verti-objects'], width, config['border-data'].separator) + '\n';
			}

			// génération de la bordure de l'exemple 
			svgContent += '\n' + genExBorder(
				config.class['example-border'],
				'' + i,
				config.margins.left - config.margins['inter-border'],
				config.margins.top + i * (config.object.height + config.margins['verti-objects']) - config.margins['inter-border'],
				model[i].length * config.object.width + (model[i].length - 1) * config.margins['hori-objects'] + 2 * config.margins['inter-border'],
				config.object.height + 2 * config.margins['inter-border'],
				config['border-data'].example
			) + '\n';

			for (var j = 0; j < model[i].length; ++j) {
				// génération des objets
				svgContent += '\n' + genShapeValue(
					config.shapes[model[i][j].forme],
					config.margins.left + j * config.object.width + (j * config.margins['hori-objects']),
					config.margins.top + i * config.object.height + (i * config.margins['verti-objects']),
					config.object.width,
					config.object.height,
					config.colors[model[i][j].couleur]) + '\n';

				// ajout taille de l'objet
				svgContent += '\n' + genTextValue(
					model[i][j].taille,
					config.margins.left + j * config.object.width + (j * config.margins['hori-objects']),
					config.margins.top + i * config.object.height + (i * config.margins['verti-objects']),
					0.5 * config.object.width,
					0.5 * config.object.height,
					config.font['object-size'].size,
					config.font['object-size'].color) + '\n';

				// ajout ID de l'objet
				svgContent += '\n' + genTextValue(
					j,
					config.margins.left + j * config.object.width + (j * config.margins['hori-objects']),
					config.margins.top + i * config.object.height + (i * config.margins['verti-objects']),
					0.6 * config.font['object-id'].size,
					0.7 * config.font['object-id'].size,
					config.font['object-id'].size,
					config.font['object-id'].color) + '\n';

				// ajout des relations
				if (relations['' + i + j]) {
					// trace un trait entre l'objet courant et le suivant
					svgContent += '\n' + genRelation(
						relations['' + i + j],
						config.margins.left + j * config.object.width + (j * config.margins['hori-objects']) + config.object.width,
						config.margins.top + i * config.object.height + (i * config.margins['verti-objects']) + 0.5 * config.object.height,
						config.margins['hori-objects'],
						config.font.relations,
						config['border-data'].relations) + '\n';
				}

				// ajout de la bordure de l'objet
				svgContent += '\n' + genObjBorder(
					config.class['object-border'],
					i,
					j,
					config.margins.left + j * config.object.width + (j * config.margins['hori-objects']),
					config.margins.top + i * config.object.height + (i * config.margins['verti-objects']),
					config.object,
					config['border-data'].objects) + '\n';
			}

			// génération de l'id de l'example
			svgContent += '\n' + genExId(i, config['border-data']['example-id'].radius, config.margins.top + (i + 0.5) * config.object.height + i * config.margins['verti-objects'], config.font['example-id'], config['border-data']['example-id']) + '\n';
		}
		element.innerHTML = svgContent;
		element.setAttribute('viewBox', '0 0 ' + width + ' ' + height);
		element.classList.add(id);
	};
})();

var SVGmodel = [
    [{
        taille: 1,
        forme: 'cercle',
        couleur: 'jaune'
    }, {
        taille: 2,
        forme: 'carré',
        couleur: 'rouge'
    }, {
        taille: 5,
        forme: 'triangle',
        couleur: 'bleu'
    }],
    [{
        taille: 2,
        forme: 'cercle',
        couleur: 'jaune'
    }, {
        taille: 2,
        forme: 'rectangle',
        couleur: 'rouge'
    }],
    [{
        taille: 3,
        forme: 'cercle',
        couleur: 'rouge'
    }, {
        taille: 2,
        forme: 'trapèze',
        couleur: 'rouge'
    }, {
        taille: 4,
        forme: 'carré',
        couleur: 'vert'
    }]
];
var SVGrelations = {
    '00': 'sur',
    '10': 'sur',
    '20': 'sur'
};

var SVGconfig = {
    'object': {
        'width': 50,
        'height': 50
    },
    'margins': {
        'top': 20,
        'bottom': 20,
        'left': 50,
        'right': 30,
        'hori-objects': 40,
        'verti-objects': 40,
        'inter-border': 10
    },
    'font': {
        'object-size': {
            size: 12,
            color: 'hsl(0, 0%, 13%)'
        },
        'relations': {
            size: 8,
            color: 'hsl(0, 0%, 60%)'
        },
        'example-id': {
            size: 8,
            color: 'hsl(0, 0%, 60%)'
        },
        'object-id': {
            size: 10,
            color: 'hsl(0, 0%, 40%)'
        }
    },
    'border-data': {
        'example': {
            color: 'white',
            size: '1'
        },
        'objects': {
            color: 'white',
            size: 1
        },
        'relations': {
            color: 'hsl(0, 0%, 40%)',
            size: 1
        },
        'separator': {
            color: 'hsl(0, 0%, 30%)',
            size: 0.5
        },
        'example-id': {
            color: 'hsl(0, 0%, 40%)',
            'size': 0.5,
            'radius': 10
        }
    },
    'class': {
        'example-border': [
            'ae-ex-%id'
        ],
        'object-border': [
            'ae-obj-%ex%obj'
        ],
    },
    'colors': {
        'jaune': 'hsl(54, 92%, 48%)',
        'rouge': 'hsl(2, 80%, 68%)',
        'bleu': 'hsl(210, 60%, 55%)',
        'vert': 'hsl(121, 28%, 63%)'
    },
    'shapes': {
        'cercle': {
            'item': '<circle cx="%x" cy="%y" r="%-r" fill="%color" />',
            'x': 0.5,
            'y': 0.5,
            '-r': 0.3
        },
        'carré': {
            'item': '<polygon points="%x1,%y1 %x2,%y2 %x3,%y3 %x4,%y4" fill="%color" />',
            'x1': 0.2,
            'y1': 0.2,
            'x2': 0.8,
            'y2': 0.2,
            'x3': 0.8,
            'y3': 0.8,
            'x4': 0.2,
            'y4': 0.8
        },
        'rectangle': {
            'item': '<polygon points="%x1,%y1 %x2,%y2 %x3,%y3 %x4,%y4" fill="%color" />',
            'x1': 0.2,
            'y1': 0.35,
            'x2': 0.8,
            'y2': 0.35,
            'x3': 0.8,
            'y3': 0.65,
            'x4': 0.2,
            'y4': 0.65
        },
        'triangle': {
            'item': '<polygon points="%x1,%y1 %x2,%y2 %x3,%y3" fill="%color" />',
            'x1': 0.2,
            'y1': 0.8,
            'x2': 0.8,
            'y2': 0.8,
            'x3': 0.5,
            'y3': 0.2,
        },
        'trapèze': {
            'item': '<polygon points="%x1,%y1 %x2,%y2 %x3,%y3 %x4,%y4" fill="%color" />',
            'x1': 0.4,
            'y1': 0.2,
            'x2': 0.8,
            'y2': 0.2,
            'x3': 0.6,
            'y3': 0.8,
            'x4': 0.2,
            'y4': 0.8
        }
    }
};