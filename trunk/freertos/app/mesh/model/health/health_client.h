#ifndef HERLTH_CLIENT__H
#define HERLTH_CLIENT__H
#include "mesh_env.h"
#include "mesh_model.h"

typedef struct
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;
	void *rfu;
}health_client_t;

void health_fault_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size);

void health_period_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size);

void health_attention_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size);
#endif


