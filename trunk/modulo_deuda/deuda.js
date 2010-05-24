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
	url_controlador_modulo = "../modulo_deuda/deuda.php";
	actualizarHistorialDeudas();
}

function mostrarPanel()
{
	ajax('accion=mostrarPanel', false, mostrarNuevoModulo_ajax, false);
}

function actualizarValor(fila_id,nombre_campo, evento)
{
	if(evento == 13)
	{
		var arreglo_id = fila_id.split("_");
		var hiv_id = arreglo_id[(arreglo_id.length - 1)];
		var valor_nuevo = $('#'+fila_id).val();
		ajax('accion=actualizarValor&hiv_id='+hiv_id+"&valor_nuevo="+valor_nuevo+"&nombre_campo="+nombre_campo, false, actualizarAjax, false);
		return true;
	}
	else
		return false;
}

function actualizarAjax(actualizo)
{
	if(actualizo)
		console.log("actualizado!");
	else
		console.log("no se actualizo ningun valor de la fila");
}

function actualizarEstadoPago(id_fila, ultimo_clic)
{
	if(mensajeConfirmar())
	{
		var hiv_pago = $('#hiv_chk_pago_'+id_fila).attr('checked');
		var hiv_es_tiempo_gratis = $('#hiv_chk_gratis_'+id_fila).attr('checked');
		ajax("accion=actualizarEstadoPago&id_fila="+id_fila+"&hiv_pago="+hiv_pago+"&hiv_es_tiempo_gratis="+hiv_es_tiempo_gratis+"&ultimo_clic="+ultimo_clic, null, actualizarEstadoPagoAjax, null);
	}
	else
	{
		$('#hiv_chk_pago_'+id_fila).removeAttr('checked');
		$('#hiv_chk_gratis_'+id_fila).removeAttr('checked');
	}
}

function actualizarEstadoPagoAjax(actualizo)
{
	if(actualizo)
		actualizarHistorialDeudas(actualizo);
	else
		console.log('Error actualizando estado del pago');
}

function actualizarHistorialDeudas()
{
	ajax("accion=actualizarHistorialDeudas", null, actualizarHistorialDeudasAjax, null);
}

function actualizarHistorialDeudasAjax(info_servicios)
{
	$("#historial_deudas").children().remove();
	$("#historial_deudas").html(info_servicios);
}