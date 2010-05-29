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
var url_controlador_modulo = "";

function nada(){}
function before(){alert('before');}
function success(){alert('success');}
function error(){alert('error');}

function ajax(data_string, before_send_func, success_func, error_func)
{
	if(!before_send_func)
		before_send_func = nada;
	if(!success_func)
		success_func = nada;
	if(!error_func)
		error_func = nada;
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		url_controlador_modulo,
		data:		data_string,
		beforeSend:	before_send_func,
		success:	success_func,
		timeout:	30000,
		error:		error_func
	}); 
	return false;
}

function mostrarNuevoModulo_ajax(moduloNuevo)
{
	$('#div_cuerpo').empty();
	$('#div_cuerpo').append(moduloNuevo);
}

function mensajeConfirmar()
{
	if(confirm("Esta seguro?"))
		return true;
	else 
		return false;
}

function mensajeError()
{
	alert("Hubo un error");
}

$(document).ready(inicializar);

function inicializar()
{
	url_controlador_modulo = "panel.php";
	$('#con_fecha').datepicker({  dateFormat: 'yy-mm-dd',
                                onSelect: function(dateText, inst){ 
                                  ajax('accion=mostrarModulo&nombre_modulo=contabilidad&con_fecha='+$("#con_fecha").val(), false, mostrarNuevoModulo_ajax, false); 
                                }
                              });
}