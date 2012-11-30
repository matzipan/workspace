try:
	application = None

	import sys 
	from util import *
	from CLIInput import *
	from CLIOutput import *
	from CLIMedia import *

	application = Application(CLIMedia(CLIInput(), CLIOutput()), MemoryUsersRepository(), 
		MemoryDataRepository(), MemoryBillRepository())

	application.run() 
except Error: 
	"""
		If your exception reaches this point, it's either you are _bad_ programmer 
		or a fatal circumstance
	"""

	print "You should never see this message. If you do see it, something pretty ridiculous happened"

	if isinstance(application, Application):
		application.exit() 

