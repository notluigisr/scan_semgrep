    int BSONTool::run() {
        _objcheck = hasParam( "STR" );

        if ( hasParam( "STR" ) )
            _matcher.reset( new Matcher( fromjson( getParam( "STR" ) ) ) );

        return doRun();
    }