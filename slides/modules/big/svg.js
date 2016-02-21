var genSVG = null;
var genTable = null;
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

		var receptacle = document.createElement('div');
		var svgFrag = '<svg>' + svgContent + '</svg>';
		receptacle.innerHTML = ''+svgFrag;
		Array.prototype.slice.call(receptacle.childNodes[0].childNodes).forEach(function(e) {
			element.appendChild(e);
		});
		element.setAttribute('viewBox', '0 0 ' + width + ' ' + height);
		element.classList.add(id);
	};

	// gen the right table (empty, with index and example indexes)
	// gen the empty solutions array too
	genTable = function(id, table, ex) {
		table.classList.add(id);
		var header = document.createElement('div');
		header.classList.add('line');
		var indexHeader = document.createElement('span');
		indexHeader.innerHTML = "indice";
		var indexRel= document.createElement('span');
		indexRel.innerHTML = "Rel";
		var combiSize = document.createElement('span');
		combiSize.innerHTML = "Taille";
		var combiShape = document.createElement('span');
		combiShape.innerHTML = "Forme";
		var combiColor = document.createElement('span');
		combiColor.innerHTML = "Couleurs";
		header.appendChild(indexHeader);
		for (var i = 0; i < ex.length; ++i) {
			(function() {
				var cur = document.createElement('span');
				cur.innerHTML = i;
				header.appendChild(cur);
			})();
		}
		header.appendChild(indexRel);
		header.appendChild(combiSize);
		header.appendChild(combiShape);
		header.appendChild(combiColor);
		table.appendChild(header);

		var index = 0;
		for (var i = 0; i < ex[0].length; ++i) {
			for (var j = 0; j < ex[1].length; ++j) {
				for (var k = 0; k < ex[2].length; ++k) {
					(function() {
						var tr = document.createElement('div');
						tr.classList.add('line');
						tr.classList.add('ae-index-' + index);
						tr.classList.add('ae-combi-0-' + i);
						tr.classList.add('ae-combi-1-' + j);
						tr.classList.add('ae-combi-2-' + k);
						tr.innerHTML = '<span>' + index + '</span>' +
							'<span class="index ae-iex-0">' + i + '</span>' +
							'<span class="index ae-iex-1">' + j + '</span>' +
							'<span class="index ae-iex-2">' + k + '</span>' +
							'<span></span><span></span><span></span><span></span>';
						table.appendChild(tr);
					})();
					++index;
				}
			}
		}
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

function AEengine(model) {
	var events = {
		'begin': function() {

		},
		'new-example': function() {

		},
		'new-object': function() {

		},
		'end-object': function() {

		},
		'end-example': function() {

		},
		'end': function() {

		},
		'combi-line': function() {

		}
	};
	var shapeCombi = {
		'cercle': 'cercle',
		'trapèze': 'trapèze',
		'carré': 'carré',

		'cercle-trapèze': 'quelconque',
		'cercle-carré': 'quelconque',
		'rectangle-cercle': 'quelconque',
		'rectangle-trapèze': 'quadrilatère',
		'rectangle-carré': 'rectangle',
		'rectangle-quelconque': 'quelconque',
		'rectangle-quadrilatère': 'quadrilatère',
		'polygone-triangle': 'polygone',

		'cercle-quelconque': 'quelconque',
		'cercle-quadrilatère': 'quelconque',
		'cercle-parallelogramme': 'quelconque',
		'cercle-triangle': 'quelconque',
		'carré-quelconque': 'quelconque',
		'carré-quadrilatère': 'quadrilatère',
		'carré-parallelogramme': 'parallelogramme',
		'triangle-quelconque': 'quelconque',
		'triangle-quadrilatère': 'polygone',
		'triangle-parallelogramme': 'polygone',
		'triangle-rectangle': 'polygone'
	};

	// attributes combination functions
	function fusionShape(shape, shape2) {
		if (shape == '') return shape2;
		for (var i in shapeCombi) {
			if (i.indexOf(shape) != -1 && i.indexOf(shape2) != -1) {
				return shapeCombi[i];
			}
		}
	}

	function fusionInter(inter, value) {
		if (inter.min == -1) return {
			min: value,
			max: value
		};
		if (value < inter.min) {
			inter.min = value;
		} else if (value > inter.max) {
			inter.max = value;
		}
		return inter;
	}

	function fusionColor(colors, color) {
		if (colors.indexOf(color) === -1) {
			colors.push(color);
		}
		return colors;
	}

	// take a solution and output a string that describes it
	function genPrint(sol) {
		var ret = "<span>Forme : </span>" + sol.shape +
			", <span>couleurs : </span>(" + sol.color + "), <span>taille : </span>[" +
			sol.inter.min + ";" + sol.inter.max + "]";
		return ret;
	}

	// make the combination of an object and a solution
	function combi(index, ex, obj) {
		solutions[index].inter = fusionInter(solutions[index].inter, model[ex][obj].taille);
		solutions[index].color = fusionColor(solutions[index].color, model[ex][obj].couleur);
		solutions[index].shape = fusionShape(solutions[index].shape, model[ex][obj].forme);
	}

	var solutions = {};
	var index = 0;
	for (var i = 0; i < model[0].length; ++i) {
		for (var j = 0; j < model[1].length; ++j) {
			for (var k = 0; k < model[2].length; ++k) {
				solutions['' + i + j + k] = {
					inter: {
						min: -1,
						max: -1
					},
					color: [],
					shape: '',
					'index': index
				};
				++index;
			}
		}
	}

	function getIndex(ex, object) {
		var indexes = [];
		for(var i in solutions) {
			if(i[ex] == object) {
				indexes.push(i);
			}
		}
		return indexes;
	}

	this.on = function(id, callback) {
		events[id] = callback;
	};

	this.run = function() {
		events['begin']();
		for(var i = 2; i >= 0; --i) {
			events['new-example']({
				'example': i
			});
			for(var j = 0; j < model[i].length; ++j) {
				events['new-object']({
					'example': i, // id of the example
					'object': j, // id of the object
					'indexes': getIndex(i, j), // all the indexes in the solution modified
				});
				(function(i, j) {
					var tmp = getIndex(i, j);
					for(var k = 0; k < tmp.length; ++k) {
						combi(tmp[k], i, j);
						(function(t, e) {
							events['combi-line'](JSON.parse(JSON.stringify({
								'example': i,
								'object': j,
								'index': t,
								'string': genPrint(e),
								'value': e
							})));
							
						})(tmp[k], solutions[tmp[k]])
					}
				})(i, j, solutions);
				events['end-object']({
					'example': i,
					'object': j,
					'indexes': getIndex(i, j)
				});
			}
			events['end-example']({
				'example': i
			});
		}
		events['end']();
	};

	this.getSolutions = function() {
		return solutions;
	};
}

function AEdisplay(id, model, relations, config) {
	var table = null;
	var svg = null;
	var parent = null;
	var stack = [];
	var stackPt = 0;
	var that = this;

	this.linkElement = function(element) {
		parent = element;
	};

	this.prepareTable = function() {
		table = document.createElement('div');
		table.classList.add('table');
	};

	this.prepareSvg = function() {
		svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		svg.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:xlink", "http://www.w3.org/1999/xlink");
	};

	this.init = function() {
		var tmp = document.createElement('div');

		if(svg != null) {
			parent.appendChild(tmp);
			svg.id = id;
			svg.classList.add('ae-example');
			svg.setAttribute('width', '305');
			svg.setAttribute('height', '330');
			tmp.appendChild(svg);			
		}

		if(table != null) {
			parent.appendChild(table);
		}

		if(svg != null && table != null) {
			tmp.classList.add('ae-left');
			table.classList.add('ae-right');
		}

		if(svg != null) {
			genSVG(document.querySelector('#' + id), id, config, model, relations);
		}

		if(table != null) {
			genTable(id, table, model);
		}
	};

	this.lightExample = function(ex, color) {
		var example = document.querySelector('svg.' + id + ' .ae-ex-' + ex);
		if(color) {
			example.style.stroke = color;
		}

		example.style['stroke-opacity'] = 1;
	};

	this.unlightExample = function(ex) {
		var example = document.querySelector('svg.' + id + ' .ae-ex-' + ex);
		example.style['stroke-opacity'] = 0;
		setTimeout(function() {
			example.style.stroke = config['border-data'].example.color;
		}, 400);
	};

	this.lightObject = function(ex, obj, color) {
		var obj = document.querySelector('svg.' + id + ' .ae-obj-' + ex + obj);
		if(color) {
			obj.style.stroke = color;
		}
		obj.style['stroke-opacity'] = 1;
	};

	this.unlightObject = function(ex, obj) {
		var obj = document.querySelector('svg.' + id + ' .ae-obj-' + ex + obj);
		obj.style['stroke-opacity'] = 0;
		setTimeout(function() {
			obj.style.stroke = config['border-data'].objects.color;
		}, 400);
	};

	this.setText = function(index, text) {
		var obj = document.querySelector('.table.' + id + ' .line.ae-combi-0-' + index[0] +
															'.ae-combi-1-' + index[1] +
															'.ae-combi-2-' + index[2]);
		var children = obj.querySelectorAll('span');
		children[children.length - 1].innerHTML = text.color;
		children[children.length - 2].innerHTML = text.shape;
		children[children.length - 3].innerHTML = text.size;
	};

	this.setRelation = function(index, value) {
		var obj = document.querySelector('.table.' + id + ' .line.ae-combi-0-' + index[0] +
															'.ae-combi-1-' + index[1] +
															'.ae-combi-2-' + index[2]);
		var children = obj.querySelectorAll('span');
		children[children.length - 4].innerHTML = value;
	};

	function _action(action) {
		if (action.svg) {
			if (action.svg.showExample) {
				for (var i = 0; i < action.svg.showExample.length; ++i) {
					that.lightExample(action.svg.showExample[i]);
				}
			}
			if (action.svg.showObject) {
				for (var i = 0; i < action.svg.showObject.length; ++i) {
					that.lightObject(action.svg.showObject[i][0], action.svg.showObject[i][1]);
				}
			}
		}
		if(action.text) {
			for(var i in action.text) {
				that.setText(i, action.text[i]);
			}
		}
		/*if (action.table) {
			if(action.table.comment) {
				highlight()
			}
			if (add) {
				if (action.table.comment) {
					highlight(action.table.obj, action.table.columns, 'hsl(0, 0%, 30%)', action.table.comment);
				} else {
					highlight(action.table.obj, action.table.columns, 'hsl(0, 0%, 30%)');
				}
			} else {
				highlight(action.table.obj, action.table.columns);
			}
		}*/
	};

	function _unaction(action) {
		if (action.svg) {
			if (action.svg.showExample) {
				for (var i = 0; i < action.svg.showExample.length; ++i) {
					that.unlightExample(action.svg.showExample[i]);
				}
			}
			if (action.svg.showObject) {
				for (var i = 0; i < action.svg.showObject.length; ++i) {
					that.unlightObject(action.svg.showObject[i][0], action.svg.showObject[i][1]);
				}
			}
		}
	};

	this.addAction = function(action) {
		stack.push([true, action]);
	};

	this.addUnaction = function(action) {
		stack.push([false, action]);
	};

	this.playAnimation = function() {

	};

	this.nextStep = function() {
		if(stackPt >= stack.length);
		if(stack[stackPt][0]) {
			_action(stack[stackPt][1]);
		}
		else {
			_unaction(stack[stackPt][1]);
		}
		++stackPt;
	};
}