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

function cargarCategorias()
{
	ajax('accion=cargarCategorias', false, cargarCategoriasAjax, false);
}

function cargarCategoriasAjax(categorias)
{
	$("#td_categorias").html(categorias);
}

function actualizarParametros()
{
  var alcance = $("#opc_alcance").val();
  $("#tbl_diario").addClass("oculto");
  $("#tbl_mensual").addClass("oculto");
  $("#tbl_rango").addClass("oculto");
  $("#tbl_"+alcance).removeClass("oculto");
}

function actualizarEstadisticas()
{
  var params = $("#form_opciones").serialize();
	ajax("accion=actualizarEstadisticas&"+params, null, actualizarEstadisticasAjax, null);
}

function actualizarEstadisticasAjax(info_estadisticas)
{
	$("#tbl_estadisticas").children().remove();
	$("#tbl_estadisticas").html(info_estadisticas);
}