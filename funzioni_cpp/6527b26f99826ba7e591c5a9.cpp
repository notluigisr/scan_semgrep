static void delete_sdl_soap_binding_function_body(sdlSoapBindingFunctionBody body)
{
	if (body.ns) {
		efree(body.ns);
	}
	if (body.headers) {
		zend_hash_destroy(body.headers);
		efree(body.headers);
	}
}