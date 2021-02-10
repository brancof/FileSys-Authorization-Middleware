package helloworld;

import helloworld.resources.CodeResource;
import io.dropwizard.Application;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;
import helloworld.health.TemplateHealthCheck;
import org.eclipse.jetty.servlets.CrossOriginFilter;

import javax.servlet.DispatcherType;
import javax.servlet.FilterRegistration;
import java.util.EnumSet;

public class PermitionsApplication extends Application<PermitionsConfig> {

    public static void main(final String[] args) throws Exception {
        new PermitionsApplication().run(args);
    }

    @Override
    public String getName() {
        return "Permitions";
    }

    @Override
    public void initialize(final Bootstrap<PermitionsConfig> bootstrap) {
    }

    @Override
    public void run(final PermitionsConfig configuration,
                    final Environment environment) {
        final FilterRegistration.Dynamic cors =
                environment.servlets().addFilter("CORS", CrossOriginFilter.class);

        // Configure CORS parameters
        cors.setInitParameter(CrossOriginFilter.ALLOWED_ORIGINS_PARAM, "*");
        cors.setInitParameter(CrossOriginFilter.ALLOWED_HEADERS_PARAM, "X-Requested-With,Content-Type,Accept,Origin,Authorization");
        cors.setInitParameter(CrossOriginFilter.ALLOWED_METHODS_PARAM, "OPTIONS,GET,PUT,POST,DELETE,HEAD");
        cors.setInitParameter(CrossOriginFilter.ALLOW_CREDENTIALS_PARAM, "true");

        // Add URL mapping
        cors.addMappingForUrlPatterns(EnumSet.allOf(DispatcherType.class), true, "/*");
        environment.jersey().register(
            new CodeResource());
        environment.healthChecks().register("template",
            new TemplateHealthCheck(configuration.template));
    }

}
