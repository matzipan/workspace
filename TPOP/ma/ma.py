try:
	application = None

	from Application import *
	from CLIInput import *
	from CLIOutput import *
	from CLIMedia import *
	from MemoryBillRepository import *
	from MemoryDataRepository import *
	from MemoryUserRepository import *

	application = Application(CLIMedia(CLIInput(), CLIOutput()), MemoryUserRepository(), 
		MemoryDataRepository(), MemoryBillRepository())
application.run() 
except Exception: 
	"""
		If your exception reaches this point, it's either you are _bad_ programmer 
		or a fatal circumstance
	"""

	print "You should never see this message. If you do see it, something pretty ridiculous happened"

	if isinstance(application, Application):
		application.exit()