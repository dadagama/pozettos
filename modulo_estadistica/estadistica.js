/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/
$(document).ready(inicializar);

function inicializar()
{
	url_controlador_modulo = "../modulo_estadistica/estadistica.php";
	$('#opc_fecha').datepicker({ dateFormat: 'yy-mm-dd' });
	$('#opc_fecha_inicial').datepicker({ dateFormat: 'yy-mm-dd' });
	$('#opc_fecha_final').datepicker({ dateFormat: 'yy-mm-dd' });
	cargarCategorias();
}

function mostrarModulo(nombre_modulo)
{
	ajax('accion=mostrarModulo&nombre_modulo='+nombre_modulo, false, mostrarNuevoModulo_ajax, false);
}

function cargarCategorias()
{
	ajax('accion=cargarCategorias', false, cargarCategoriasAjax, false);
}

function cargarCategoriasAjax(categorias)
{
	$("#td_categorias").html(categorias);
}

function actualizarEstadisticas()
{
	ajax("accion=actualizarEstadisticas", null, actualizarEstadisticasAjax, null);
}

function actualizarEstadisticasAjax(info_estadisticas)
{
	$("#historial_estadisticas").children().remove();
	$("#historial_estadisticas").html(info_estadisticas);
}