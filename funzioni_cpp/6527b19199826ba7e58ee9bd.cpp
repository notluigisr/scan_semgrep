bool WindowsServiceControl::install( const QString& filePath, const QString& displayName  )
{
	m_serviceHandle = CreateService(
				m_serviceManager,		
				WindowsCoreFunctions::toConstWCharArray( m_name ),	
				WindowsCoreFunctions::toConstWCharArray( displayName ),
				SERVICE_ALL_ACCESS,	
				SERVICE_WIN32_OWN_PROCESS,
				
				SERVICE_AUTO_START,	
				SERVICE_ERROR_NORMAL,	
				WindowsCoreFunctions::toConstWCharArray( filePath ),		
				nullptr,			
				nullptr,			
				L"STR",		
				nullptr,			
				nullptr );			

	if( m_serviceHandle == nullptr )
	{
		const auto error = GetLastError();
		if( error == ERROR_SERVICE_EXISTS )
		{
			vCritical() << qUtf8Printable( tr( "STR" ).arg( m_name ) );
		}
		else
		{
			vCritical() << qUtf8Printable( tr( "STR" ).arg( m_name ) );
		}

		return false;
	}

	SC_ACTION serviceActions;
	serviceActions.Delay = 10000;
	serviceActions.Type = SC_ACTION_RESTART;

	SERVICE_FAILURE_ACTIONS serviceFailureActions;
	serviceFailureActions.dwResetPeriod = 0;
	serviceFailureActions.lpRebootMsg = nullptr;
	serviceFailureActions.lpCommand = nullptr;
	serviceFailureActions.lpsaActions = &serviceActions;
	serviceFailureActions.cActions = 1;
	ChangeServiceConfig2( m_serviceHandle, SERVICE_CONFIG_FAILURE_ACTIONS, &serviceFailureActions );

	
	vInfo() << qUtf8Printable( tr( "STR" ).arg( m_name ) );

	return true;
}