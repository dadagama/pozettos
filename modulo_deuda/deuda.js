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
	if($('#vep_cli_id').val())
	{
		actualizarHistoricoProductos();
		actualizarHistoricoServicios();
	}
}

function actualizarEstadoDeuda(id_fila, estado, prefijo)
{
	ajax("accion=actualizarEstadoDeuda&prefijo="+prefijo+"&id_fila="+id_fila+"&estado="+estado, null, actualizarEstadoDeudaAjax, null);
}

function actualizarEstadoDeudaAjax(prefijo)
{
	if(prefijo == "vep")
		actualizarHistoricoProductos();
	else if(prefijo == "ves")
		actualizarHistoricoServicios();
	else
		alert('Error inesperado actualizando estado de la deuda');
}

function actualizarObservacion(key_code, id_fila, prefijo)
{
	if(key_code == 13)
	{
		var observacion = $("#"+prefijo+"_observacion_"+id_fila).val();
		ajax("accion=actualizarObservacion&prefijo="+prefijo+"&id_fila="+id_fila+"&observacion="+observacion, null, null, null);
	}
}

function actualizarListaClientes(key_code)
{
	if(key_code == 13)
	{
		var info_cliente = $("#buscar_cliente").val();
		ajax("accion=actualizarListaClientes&info_cliente="+info_cliente, null, actualizarListaClientesAjax, null);
	}
}

function actualizarListaClientesAjax(opciones_clientes)
{
	$("#cli_id").children().remove();
	$("#cli_id").html(opciones_clientes);
}


/**********************************
******* ACCIONES PRODUCTOS  *******
***********************************/

function actualizarHistoricoProductos()
{
	var cli_id = $("#vep_cli_id").val();
	ajax("accion=actualizarHistoricoProductos&cli_id="+cli_id, null, actualizarHistoricoProductosAjax, null);
}

function actualizarHistoricoProductosAjax(info_productos)
{
	$("#vep_historial").children().remove();
	$("#vep_historial").html(info_productos);
}

/**********************************
******* ACCIONES SERVICIOS  *******
***********************************/

function actualizarHistoricoServicios()
{
	var cli_id = $("#vep_cli_id").val();
	ajax("accion=actualizarHistoricoServicios&cli_id="+cli_id, null, actualizarHistoricoServiciosAjax, null);
}

function actualizarHistoricoServiciosAjax(info_productos)
{
	$("#ves_historial").children().remove();
	$("#ves_historial").html(info_productos);
}