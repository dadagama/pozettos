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

/**********************************
******* ACCIONES GENERICAS  *******
***********************************/

$(document).ready(inicializar);

function inicializar()
{
	actualizarHoraInicio();
	url_controlador_modulo = "../modulo_contabilidad/contabilidad.php";
	actualizarHistoricoProductos();
	actualizarHistoricoServicios();
	obtenerInfoTimers();
}

function mostrarPanel()
{
	ajax('accion=mostrarPanel', false, mostrarNuevoModulo_ajax, false);
}

function asignarListenersColores(prefijo)
{
	var arreglo_filas = document.getElementsByName(prefijo+'_fila');//listeners productos
	for(var x = 0; x < arreglo_filas.length ; x++)
	{
		//el ID tiene la forma ==> vep_fila_#
		var consecutivo = arreglo_filas[x].id.split("_")[2];
		$("#"+prefijo+"_color_"+consecutivo).attachColorPicker();
			$("#"+prefijo+"_color_"+consecutivo).change(
				function() {cambiarColorFila(this);}
			);
	}
}

function cambiarColorFila(elemento)
{
	//el ID tiene la forma ==> <prefijo>_color_<#>
	var consecutivo = elemento.id.split("_")[2];
	var color = $("#"+elemento.id).getValue();
	var prefijo = elemento.id.split("_")[0];
	actualizarCampoColor(consecutivo, color, prefijo);
	
}

function actualizarListaClientes(key_code, prefijo)
{
	if(key_code == 13)
	{
		var info_cliente = $("#"+prefijo+"_buscar_cliente").val();
		var funcion_ajax = "";
		if(prefijo == "vep")
			funcion_ajax = actualizarListaClientesProductoAjax;
		else if(prefijo == "ves")
			funcion_ajax = actualizarListaClientesServicioAjax;
		else
		alert('Error inesperado al actualizar lista de clientes');
		ajax("accion=actualizarListaClientes&info_cliente="+info_cliente, null, funcion_ajax, null);
	}
}

function actualizarCampoColor(id, color_fila, prefijo)
{
	ajax("accion=actualizarCampoColor&prefijo="+prefijo+"&"+prefijo+"_id="+id+"&"+prefijo+"_color_fila="+color_fila, null, actualizarCampoColorAjax, null);
}

function actualizarCampoColorAjax(prefijo_actualizacion)
{
	if(prefijo_actualizacion == "vep")
		actualizarHistoricoProductos();
	else if(prefijo_actualizacion == "ves")
		actualizarHistoricoServicios();
	else
		alert("error inesperado actualizando color");
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

function eliminarFila(id, prefijo)
{
	ajax("accion=eliminarFila&id="+id+"&prefijo="+prefijo, mensajeConfirmar, eliminarFilaAjax, null);
}

function eliminarFilaAjax(id_eliminado)
{
	if(id_eliminado)
		$("#"+id_eliminado).remove();
}

function actualizarObservacion(key_code, id_fila, prefijo)
{
	if(key_code == 13)
	{
		var observacion = $("#"+prefijo+"_observacion_"+id_fila).val();
		ajax("accion=actualizarObservacion&prefijo="+prefijo+"&id_fila="+id_fila+"&observacion="+observacion, null, null, null);
	}
}

/**********************************
******* ACCIONES PRODUCTOS  *******
***********************************/

function actualizarListaClientesProductoAjax(opciones_clientes)
{
	$("#vep_cli_id").children().remove();
	$("#vep_cli_id").html(opciones_clientes);
}

function agregarFilaProducto()
{
	var vep_cli_id = $("#vep_cli_id").val();
	var vep_pro_id = $("#vep_pro_id").val();
	var vep_total = $("#vep_total").val();
	//se guarda la fecha del producto vendido deacuerdo a
	//la fecha de la contabilidad abierta actualmente
	var vep_fecha_venta = "";
	var fecha_actual = new Date();
	var anno_actual = fecha_actual.getFullYear();
	var mes_actual = fecha_actual.getMonth() + 1;
	if(mes_actual < 10)
		mes_actual = "0"+mes_actual;
	var dia_actual = fecha_actual.getDate();
	var hora_actual = fecha_actual.getHours();
	var minuto_actual = fecha_actual.getMinutes();
	var segundo_actual = fecha_actual.getSeconds();
	if($("#fecha_contabilidad").val() != anno_actual+"-"+mes_actual+"-"+dia_actual)
		vep_fecha_venta = $("#fecha_contabilidad").val()+" "+hora_actual+":"+minuto_actual+":"+segundo_actual;

	ajax("accion=agregarFilaProducto&vep_cli_id="+vep_cli_id+
				"&vep_pro_id="+vep_pro_id+
				"&vep_total="+vep_total+
				"&vep_fecha_venta="+vep_fecha_venta, null, agregarFilaProductoAjax, null);
}

function agregarFilaProductoAjax(fila)
{
	if(fila)
	{
		actualizarHistoricoProductos();
		reiniciarFormularioProducto();
	}
	else
		alert('Error inesperado al agregar una fila de producto');
}

function actualizarHistoricoProductos()
{
	ajax("accion=actualizarHistoricoProductos", null, actualizarHistoricoProductosAjax, null);
}

function actualizarHistoricoProductosAjax(info_productos)
{
	$("#vep_historial").children().remove();
	$("#vep_historial").html(info_productos);
	asignarListenersColores('vep');
}

function reiniciarFormularioProducto()
{
	$("#vep_cli_id").val(1);
	$("#vep_pro_id").val(1);
	$("#vep_total").val(0);
	$("#vep_buscar_cliente").val("");
	actualizarListaClientes(13, "vep");
}

/**********************************
******* ACCIONES SERVICIOS  *******
***********************************/

function actualizarListaClientesServicioAjax(opciones_clientes)
{
	$("#ves_cli_id").children().remove();
	$("#ves_cli_id").html(opciones_clientes);
}

function agregarFilaServicio()
{
	var ves_ser_id = $("#ves_ser_id").val();
	var ves_hora = $("#ves_hora").val();
	var ves_minuto = $("#ves_minuto").val();
	var ves_meridiano = $("#ves_meridiano").val();
	var ves_duracion = $("#ves_duracion").val();
	var ves_total = $("#ves_total").val();
	var ves_cli_id = $("#ves_cli_id").val();
	//alert(ves_ser_id+" - "+ves_hora+":"+ves_minuto+" "+ves_meridiano+" - "+ves_duracion+" - "+ves_total+" - "+ves_cli_id);
	//se guarda la fecha del producto vendido deacuerdo a
	//la fecha de la contabilidad abierta actualmente
	var ves_fecha = "";
	var fecha_actual = new Date();
	var anno_actual = fecha_actual.getFullYear();
	var mes_actual = fecha_actual.getMonth() + 1;
	if(mes_actual < 10)
		mes_actual = "0"+mes_actual;
	var dia_actual = fecha_actual.getDate();
	if($("#fecha_contabilidad").val() != anno_actual+"-"+mes_actual+"-"+dia_actual)
		ves_fecha = $("#fecha_contabilidad").val();
		
	ajax("accion=agregarFilaServicio&ves_ser_id="+ves_ser_id+
				"&ves_hora="+ves_hora+
				"&ves_minuto="+ves_minuto+
				"&ves_meridiano="+ves_meridiano+
				"&ves_duracion="+ves_duracion+
				"&ves_total="+ves_total+
				"&ves_cli_id="+ves_cli_id+
				"&ves_fecha="+ves_fecha, null, agregarFilaServicioAjax, null);
}

function agregarFilaServicioAjax(fila)
{
	if(fila)
	{
		actualizarHistoricoServicios();
		reiniciarFormularioServicio();
	}
	else
		alert('Error al tratar de agregar una fila en servicios');
}

function actualizarHistoricoServicios()
{
	ajax("accion=actualizarHistoricoServicios", null, actualizarHistoricoServiciosAjax, null);
}

function actualizarHistoricoServiciosAjax(info_servicios)
{
	$("#ves_historial").children().remove();
	$("#ves_historial").html(info_servicios);
	asignarListenersColores('ves');
}

function reiniciarFormularioServicio()
{
	$("#ves_ser_id").val(1);
	$("#ves_duracion").val('00:00:00');
	$("#ves_total").val(0);
	$("#ves_cli_id").val(1);
	$("#ves_buscar_cliente").val("");
	actualizarListaClientes(13, "ves");
}

function actualizarTotalServicio()
{
	var servicio = $("#ves_ser_id").val();
	var duracion = $("#ves_duracion").val();
	ajax("accion=actualizarTotalServicio&servicio="+servicio+"&duracion="+duracion, null, actualizarTotalServicioAjax, null);
}

function actualizarTotalServicioAjax(total)
{
	$("#ves_total").val(total);
}

function actualizarHoraInicio()
{
	var fecha = new Date();
	var hora = fecha.getHours();
	var minutos = fecha.getMinutes();
	var minuto_digito_derecha = "0";
	var minuto_digito_izquierda = "0"; //no siempre existe

	if(minutos > 9)
	{
		minuto_digito_izquierda = (""+minutos)[0];
		minuto_digito_derecha = (""+minutos)[1];
	}
	else
		minuto_digito_derecha = (""+minutos)[0];
	
	var minutos_redondeados = "99";
	if(parseInt(minuto_digito_derecha) < 5)
		minutos_redondeados = minuto_digito_izquierda+"5";
	else
	{
		var nuevo_digito_izquierda = parseInt(minuto_digito_izquierda)+1;
		if(nuevo_digito_izquierda < 6)
			minutos_redondeados = nuevo_digito_izquierda+"0";
		else
		{
			minutos_redondeados = "00";
			hora++;
		}
	}
	var meridiano = "99";
	if(hora < 12)
		meridiano = "am";
	else
	{
		meridiano = "pm";
		if(hora != 12)
			hora = hora - 12;
	}
	if(hora == 0)
		hora = 12;
	
	$("#ves_hora").val(""+hora);
	$("#ves_minuto").val(""+parseInt(minutos_redondeados));
	$("#ves_meridiano").val(meridiano);
}

function actualizarDuracionYTotalServicio(id)
{
	var duracion = $("#ves_duracion_"+id).val();
	ajax("accion=actualizarDuracionYTotalServicio&id="+id+"&duracion="+duracion, null, actualizarDuracionYTotalServicioAjax, null);
}

function actualizarDuracionYTotalServicioAjax(actualizo)
{
	if(actualizo)
		actualizarHistoricoServicios();
	else
		alert('Error inesperado actualizando Duracion y total de servicio');
}

/**********************************
******* ACCIONES TIMERS     *******
***********************************/

var arreglo_CronoID;
var arreglo_CronoEjecutandose;
var arreglo_bandera_incrementa;
var arreglo_segundos = new Array(5); 
var arreglo_minutos = new Array(5);
var arreglo_horas = new Array(5);

function obtenerInfoTimers()
{
	ajax("accion=obtenerInfoTimers", null, obtenerInfoTimersAjax, null);
}

function obtenerInfoTimersAjax(json_timers)
{
	var obj_timers = eval('('+json_timers+')');
		
	arreglo_bandera_incrementa = new Array(obj_timers.length);
	arreglo_CronoEjecutandose = new Array(obj_timers.length);
	arreglo_CronoID = new Array(obj_timers.length);
	arreglo_segundos = new Array(obj_timers.length);
	arreglo_minutos = new Array(obj_timers.length);
	arreglo_horas = new Array(obj_timers.length);
	
	for(var x = 0; x < obj_timers.length; x++)
	{
		var duracion_timer = obj_timers[x].tim_dus_minutos.split(":");
		$('#tim_duracion_horas_'+x).val(duracion_timer[0]);
		$('#tim_duracion_minutos_'+x).val(duracion_timer[1]);
		//inicializo arreglos
		arreglo_bandera_incrementa[x] = (obj_timers[x].tim_es_incremental == 1) ? true : false;
		arreglo_CronoEjecutandose[x] = (obj_timers[x].tim_esta_ejecutando == 1) ? true : false;
		if(arreglo_bandera_incrementa[x] == true) //si es incremental (tiempo libre)
		{
			var tiempo_inicia = obj_timers[x].tim_inicia;
			var tiempo_lleva = obj_timers[x].tim_lleva;
			if(tiempo_lleva.length >= 9) //error porque tiempo es mas de 99 horas!
				arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = '99';
			else
			{
				arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = 0;
				var arreglo_tiempo_lleva = tiempo_lleva.split(":");
				arreglo_segundos[x] = parseInt(arreglo_tiempo_lleva[2]);
				arreglo_minutos[x] = parseInt(arreglo_tiempo_lleva[1]);
				arreglo_horas[x] = parseInt(arreglo_tiempo_lleva[0]);
			}
		}
		else //si es decremental (tiempo prefijado)
		{
			var tiempo_finaliza = obj_timers[x].tim_finaliza;
			var tiempo_falta = obj_timers[x].tim_falta;
			if(tiempo_falta.length >= 9)//error porq ya es negativo, se paso!
				arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = '99';
			else
			{
				arreglo_segundos[x] = arreglo_minutos[x] = arreglo_horas[x] = 0;
				var arreglo_tiempo_falta = tiempo_falta.split(":");
				arreglo_segundos[x] = parseInt(arreglo_tiempo_falta[2]);
				arreglo_minutos[x] = parseInt(arreglo_tiempo_falta[1]);
				arreglo_horas[x] = parseInt(arreglo_tiempo_falta[0]);
			}
		}
	}
	for(var y = 0; y < obj_timers.length; y++)
	{
		if(arreglo_CronoEjecutandose[y] == true)//si se esta ejecutando
			IniciarCrono(y);
		else//si no esta ejecutandose
		{
			
		}
	}
}

function DetenerCrono (pos)
{
	//detiene hilos
  if(arreglo_CronoEjecutandose[pos])
		clearTimeout(arreglo_CronoID[pos]);
  arreglo_CronoEjecutandose[pos] = false;
	arreglo_CronoID[pos] = null;
	//colocar boton y accion de play
	$('#img_play_pause_'+pos).attr('src', '../imagenes/play.jpg');
	$('#btn_play_pause_'+pos).attr('onClick', 'IniciarCrono('+pos+');');
}

function InicializarCrono (pos) 
{
	DetenerCrono(pos);
	arreglo_horas[pos] = parseInt($('#tim_duracion_horas_'+pos).val());
	arreglo_minutos[pos] = parseInt($('#tim_duracion_minutos_'+pos).val());
	arreglo_segundos[pos] = 0;
	var horas = (arreglo_horas[pos] < 10) ? "0" + arreglo_horas[pos] : arreglo_horas[pos];
	var minutos = (arreglo_minutos[pos] < 10) ? "0" + arreglo_minutos[pos] : arreglo_minutos[pos];
	var segundos = (arreglo_segundos[pos] < 10) ? "0" + arreglo_segundos[pos] : arreglo_segundos[pos];
	//inicializa interfaz
	$('#lbl_timer_'+pos).html(horas+":"+minutos+":"+segundos);
}

function ejecutarCrono (pos) 
{ 
	var parar = false;
	if(arreglo_bandera_incrementa[pos] == 1)
	{
		//si marca 99:99:99 se detiene
		if( arreglo_horas[pos] == 99 && arreglo_minutos[pos] == 99 && arreglo_segundos[pos] == 99)
		{
			alert('se pasaron ole! turu truu!');
			DetenerCrono(pos);
			parar = true;
		}
		else
		{
			//incrementa el crono
			arreglo_segundos[pos]++;
			if ( arreglo_segundos[pos] > 59 ) 
			{
				arreglo_segundos[pos] = 0;
				arreglo_minutos[pos]++;
				if ( arreglo_minutos[pos] > 59 ) 
				{
					arreglo_minutos[pos] = 0;
					arreglo_horas[pos]++;
				}
			}
		}
	}
	else
	{
		if( parseInt(arreglo_horas[pos]) == 99)
		{
			alert('se acabo! turu truu!');
			DetenerCrono(pos);
			parar = true;
		}
		else
		{
			//decrementa
			arreglo_segundos[pos]--;
			if ( arreglo_segundos[pos] < 0 ) 
			{
				arreglo_segundos[pos] = 59;
				arreglo_minutos[pos]--;
				if ( arreglo_minutos[pos] < 0 ) 
				{
					arreglo_minutos[pos] = 59;
					arreglo_horas[pos]--;
					if ( arreglo_horas[pos] < 0 ) 
						arreglo_horas[pos] = 99;
				}
			}
		}
	}

	//configura la salida
	var ValorCrono = "";
	ValorCrono = (arreglo_horas[pos] < 10) ? arreglo_horas[pos] : arreglo_horas[pos];
	ValorCrono += (arreglo_minutos[pos] < 10) ? ":0" + parseInt(arreglo_minutos[pos]) : ":" + arreglo_minutos[pos];
	ValorCrono += (arreglo_segundos[pos] < 10) ? ":0" + parseInt(arreglo_segundos[pos]) : ":" + arreglo_segundos[pos];
	$('#lbl_timer_'+pos).html(ValorCrono);
	if(parar)
		return false;
	arreglo_CronoID[pos] = setTimeout("ejecutarCrono("+pos+")", 1000);
	arreglo_CronoEjecutandose[pos] = true;
	return true;
}

function IniciarCrono (pos)
{
	ajax("accion=IniciarCrono&id="+pos+"&", null, obtenerInfoTimersAjax, null);
	ejecutarCrono(pos);
	//colocar boton y accion de pause
	$('#img_play_pause_'+pos).attr('src', '../imagenes/pause.jpg');
	$('#btn_play_pause_'+pos).attr('onClick', 'DetenerCrono('+pos+');');
}