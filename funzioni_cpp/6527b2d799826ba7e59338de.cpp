void ImapModelOpenConnectionTest::testPreauth()
{
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QVERIFY(SOCK->writtenStuff().isEmpty());
    SOCK->fakeReading( "STR" );
    QVERIFY( completedSpy->isEmpty() );
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QCOMPARE( SOCK->writtenStuff(), QByteArray("STR") );
    QVERIFY( completedSpy->isEmpty() );
    SOCK->fakeReading( "STR" );
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QCOMPARE( completedSpy->size(), 1 );
    QVERIFY(failedSpy->isEmpty());
    QVERIFY( authSpy->isEmpty() );
    QVERIFY(startTlsUpgradeSpy->isEmpty());
}